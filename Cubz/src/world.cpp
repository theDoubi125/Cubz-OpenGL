#include <glad/glad.h>
#include "world.h"

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
	m_data[pos.x + pos.y * m_size.x + pos.z * m_size.x * m_size.y] = value;
}

int World::getTile(ivec3 pos) const
{
	return m_data[pos.x + pos.y * m_size.x + pos.z * m_size.x * m_size.y];
}

ivec3 World::getSize() const
{
	return m_size;
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
	
	std::vector<std::vector<float> > vertices(BLOCK_TYPE_COUNT, std::vector<float>());
	std::vector<std::vector<float> > uvs(BLOCK_TYPE_COUNT, std::vector<float>());

	int arrayPos[BLOCK_TYPE_COUNT];
	memset(arrayPos, 0, BLOCK_TYPE_COUNT * sizeof(int));

	for (int i = 0; i < BLOCK_TYPE_COUNT; i++)
	{
		vertices[i].reserve(arraySize * 3 / 10);
		uvs[i].reserve(arraySize * 2 / 10);
	}

	//for each cell
	for (int x = 0; x < worldDim.x; x++)
	{
		for (int y = 0; y < worldDim.y; y++)
		{
			for (int z = 0; z < worldDim.z; z++)
			{
				// check neighbours in each direction
					// if no neighbour,
				int tileId = m_world.getTile(ivec3(x, y, z));
				if (tileId > 0)
				{
					
					vertices[tileId][arrayPos[tileId]] = 
				}
			}
		}
	}
}
