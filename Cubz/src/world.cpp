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
