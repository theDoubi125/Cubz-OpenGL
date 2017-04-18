#include <glad/glad.h>
#include "world.h"
#include "entity.h"

World::World(ivec3 size) : m_size(size), m_data(NULL)
{
	m_data = new int[size.x * size.y * size.z];
	memset(m_data, 0, sizeof(int) * (size.x * size.y * size.z));
}

World::~World()
{
	delete m_data;
}

void World::setTile(ivec3 pos, int value)
{
	int id = pos.x + pos.y * m_size.x + pos.z * m_size.x * m_size.y;
	m_data[id] = value;
}

int World::getTile(ivec3 pos) const
{
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

	int arrayPos[BLOCK_TYPE_COUNT];
	memset(arrayPos, 0, BLOCK_TYPE_COUNT * sizeof(int));

	for (int i = 0; i < BLOCK_TYPE_COUNT; i++)
	{
		vertices[i].reserve(arraySize / 10);
		uvs[i].reserve(arraySize / 10);
	}

	ivec3 directions[] =	{ IVEC_UP,		IVEC_RIGHT, IVEC_FORWARD, IVEC_DOWN,	IVEC_LEFT,		IVEC_BACK	};
	ivec3 xVec[] =			{ IVEC_RIGHT,	IVEC_BACK,	IVEC_RIGHT, IVEC_BACK,		IVEC_FORWARD,	IVEC_LEFT	};
	ivec3 yVec[] =			{ IVEC_FORWARD, IVEC_UP,	IVEC_UP,	IVEC_RIGHT,		IVEC_UP,		IVEC_UP		};

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
							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(xVec[i] - yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(1, 0));
							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(xVec[i] + yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(1, 1));

							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(-xVec[i] + yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(0, 1));
							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(-xVec[i] - yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(0, 0));
							vertices[m_world.getTile(pos)].push_back(center + 0.5f * (vec3)(xVec[i] + yVec[i]));
							uvs[m_world.getTile(pos)].push_back(ivec2(1, 1));
						}
					}
				}
			}
		}
	}

	Shader* shader = new Shader("resources/shaders/cube.vert", "resources/shaders/cube.frag");
	shader->load();
	for (int i = 0; i < BLOCK_TYPE_COUNT; i++)
	{
		setData(i, shader, vertices[i].size(), (float*)vertices[i].data(), (float*)uvs[i].data(), GL_STATIC_DRAW);
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
	for (int i = 0; i < 5; i++)
	{
		m_world.setTile(ivec3(1+i, 0, 1), 1);

	}
	m_mesh.updateData();
}

void WorldComponent::updateRender()
{
	m_mesh.updateData();
}

void WorldComponent::render() const
{
	m_mesh.render(m_entity->transform().transformMatrix());
}

World& WorldComponent::world()
{
	return m_world;
}
