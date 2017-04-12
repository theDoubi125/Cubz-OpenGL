#pragma once

#ifndef WORLD_INCLUDED
#define WORLD_INCLUDED

#include "vec.h"

/*
	World: has an array of cells identified by its ID

*/

class World
{
public:
	World(ivec3 size);
	~World();

	int getTile(ivec3 cell) const;
	void setTile(ivec3 cell, int id);

	bool hasNeighbour(ivec3 cell, ivec3 dir);

private:
	ivec3 m_size;
	int *m_data;
};

#endif
