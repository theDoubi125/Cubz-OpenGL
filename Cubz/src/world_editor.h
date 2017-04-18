#pragma once

#include "component.h"

class Mesh;

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
	virtual std::string& getName() const;

private:
	int m_selectedTile;
	float m_cursorDist;
	ivec3 m_target;
	Mesh* m_cursorMesh;
	Transform m_cursorTransform;
};