#pragma once

#ifndef WORLD_INCLUDED
#define WORLD_INCLUDED

#include "vec.h"
#include "mesh.h"

#define BLOCK_TYPE_COUNT 10

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
	ivec3 getSize() const;

private:
	ivec3 m_size;
	int *m_data;
};

class WorldMesh : Mesh
{
public:
	WorldMesh(const World& world);
	virtual ~WorldMesh();
	void updateData();

private:
	const World& m_world;
};

#endif
