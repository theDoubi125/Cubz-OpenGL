#pragma once

#ifndef WORLD_INCLUDED
#define WORLD_INCLUDED

#include "vec.h"
#include "mesh.h"
#include "component.h"

#define BLOCK_TYPE_COUNT 10

/*
	World: has an array of cells identified by its ID

*/

class World
{
public:
	World(ivec3 size);
	~World();

	int getTile(ivec3 cell, bool checkBounds = true) const;
	void setTile(ivec3 cell, int id, bool checkBounds = true);
	ivec3 getSize() const;
	bool isInBound(ivec3 cell) const;

	void load(const std::string& path);
	void save(const std::string& path) const;

private:
	ivec3 m_size;
	char *m_data;
};

class WorldMesh : public Mesh
{
public:
	WorldMesh(const World& world);
	virtual ~WorldMesh();
	void updateData();

private:
	const World& m_world;
};

class WorldComponent : public Component
{
public:
	WorldComponent();
	~WorldComponent();

	virtual Component* clone() const override;
	virtual const std::string& getName() const override { return "World"; }
	virtual void init(json descr) override;
	virtual void render() const override;
	virtual void debugUI() override;

	void updateRender();

	World& world();

private:
	World m_world;
	WorldMesh m_mesh;

	char m_filePath[100];
};

#endif
