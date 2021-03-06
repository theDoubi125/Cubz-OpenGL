#include <glad/glad.h>
#include <imgui.h>
#include <fstream>
#include "world.h"
#include "entity.h"

World::World(ivec3 size) : m_size(size), m_data(NULL)
{
	m_data = new char[size.x * size.y * size.z];
	memset(m_data, 0, sizeof(char) * (size.x * size.y * size.z));
}

World::~World()
{
	delete m_data;
}

void World::setTile(ivec3 pos, int value, bool checkBounds)
{
	if (checkBounds && !isInBound(pos))
		return;
	int id = pos.x + pos.y * m_size.x + pos.z * m_size.x * m_size.y;
	m_data[id] = value;
}

int World::getTile(ivec3 pos, bool checkBounds) const
{
	if (checkBounds && !isInBound(pos))
		return 0;
	return m_data[pos.x + pos.y * m_size.x + pos.z * m_size.x * m_size.y];
}

ivec3 World::getSize() const
{
	return m_size;
}

bool World::isInBound(ivec3 cell) const
{
	return cell.x >= 0 && cell.y >= 0 && cell.z >= 0 && cell.x < m_size.x && cell.y < m_size.y && cell.z < m_size.z;
}

void World::load(const std::string &path)
{
	std::ifstream file("resources/level/"+path, std::ios::in | std::ios::binary);
	ivec3 fileDim;
	file.read((char*)&m_size, 3 * sizeof(int));
	file.read(m_data, m_size.x * m_size.y * m_size.z);
	file.close();
}

void World::save(const std::string &path) const
{
	std::ofstream file("resources/level/" + path, std::ios::out | std::ios::binary);
	file.write((char*)&m_size, 3 * sizeof(int));
	file.write(m_data, m_size.x * m_size.y * m_size.z);

	file.close();
}


WorldMesh::WorldMesh(const World& world) : m_world(world)
{
	initData(BLOCK_TYPE_COUNT);
}

WorldMesh::~WorldMesh()
{

}

void WorldMesh::updateData()
{
	ivec3 worldDim = m_world.getSize();
	int arraySize = worldDim.x * worldDim.y * worldDim.z;
	
	std::vector<std::vector<vec3> > vertices(BLOCK_TYPE_COUNT, std::vector<vec3>());
	std::vector<std::vector<vec2> > uvs(BLOCK_TYPE_COUNT, std::vector<vec2>());
	std::vector<std::vector<vec3> > normals(BLOCK_TYPE_COUNT, std::vector<vec3>());

	int arrayPos[BLOCK_TYPE_COUNT];
	memset(arrayPos, 0, BLOCK_TYPE_COUNT * sizeof(int));

	for (int i = 0; i < BLOCK_TYPE_COUNT; i++)
	{
		vertices[i].reserve(arraySize / 10);
		uvs[i].reserve(arraySize / 10);
	}

	ivec3 directions[] =	{ IVEC_UP,		IVEC_RIGHT, IVEC_FORWARD, IVEC_DOWN,	IVEC_LEFT,		IVEC_BACK	};
	ivec3 xVec[] =			{ IVEC_FORWARD,	IVEC_BACK,	IVEC_RIGHT, IVEC_BACK,		IVEC_FORWARD,	IVEC_LEFT	};
	ivec3 yVec[] =			{ IVEC_RIGHT,	IVEC_UP,	IVEC_UP,	IVEC_RIGHT,		IVEC_UP,		IVEC_UP		};

	//for each cell
	for (int x = 0; x < worldDim.x; x++)
	{
		for (int y = 0; y < worldDim.y; y++)
		{
			for (int z = 0; z < worldDim.z; z++)
			{
				ivec3 pos = ivec3(x, y, z);
				if (m_world.getTile(pos) > 0)
				{
					// check neighbours in each direction
					for (int i = 0; i < 6; i++)
					{
						// if no neighbour, add face to the right vertex list
						if (!m_world.isInBound(pos + directions[i]) || m_world.getTile(pos + directions[i]) == 0)
						{
							vec3 center = (vec3)pos + 0.5f * (vec3)directions[i];

							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(-xVec[i] - yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(0, 0));
							normals[m_world.getTile(pos)].push_back((vec3)directions[i]);
							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(xVec[i] - yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(1, 0));
							normals[m_world.getTile(pos)].push_back((vec3)directions[i]);
							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(xVec[i] + yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(1, 1));
							normals[m_world.getTile(pos)].push_back((vec3)directions[i]);

							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(-xVec[i] + yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(0, 1));
							normals[m_world.getTile(pos)].push_back((vec3)directions[i]);
							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(-xVec[i] - yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(0, 0));
							normals[m_world.getTile(pos)].push_back((vec3)directions[i]);
							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(xVec[i] + yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(1, 1));
							normals[m_world.getTile(pos)].push_back((vec3)directions[i]);
						}
					}
				}
			}
		}
	}

	Shader* shader = new Shader("resources/shaders/basicLit.vert", "resources/shaders/basicLit.frag");
	shader->load();
	for (int i = 0; i < BLOCK_TYPE_COUNT; i++)
	{
		setData(i, shader, vertices[i].size(), (float*)vertices[i].data(), (float*)uvs[i].data(), (float*)normals[i].data(), GL_STATIC_DRAW);
	}
}


WorldComponent::WorldComponent() : m_world(ivec3(10, 10, 10)), m_mesh(m_world)
{

}

WorldComponent::~WorldComponent()
{

}

Component* WorldComponent::clone() const
{
	return new WorldComponent();
}

void WorldComponent::init(json descr)
{
	m_mesh.updateData();
}

void WorldComponent::updateRender()
{
	m_mesh.updateData();
}

void WorldComponent::render() const
{
	m_mesh.render(m_entity->transform().transformMatrix(), vec3(1, 0.5f, 0.3f));
}

World& WorldComponent::world()
{
	return m_world;
}

void WorldComponent::debugUI()
{
	ImGui::InputText("Path", m_filePath, 100);
	if (ImGui::Button("Load"))
	{
		m_world.load(m_filePath);
		updateRender();
	}
	if (ImGui::Button("Save"))
	{
		m_world.save(m_filePath);
	}
}
