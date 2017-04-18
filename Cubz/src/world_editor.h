#pragma once

#include "component.h"

class Mesh;
class WorldComponent;

class WorldEditor : public Component
{
public:
	WorldEditor();
	~WorldEditor();

	virtual void init(json descr) override;
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void render() const override;
	virtual void debugUI() override;

	virtual Component* clone() const override;
	virtual const std::string& getName() const override { return "WorldEditor"; }

private:
	int m_selectedTile;
	float m_cursorDist;
	ivec3 m_target;
	Mesh* m_cursorMesh;
	Transform m_cursorTransform;
	WorldComponent* m_world;
};
