#pragma once

#include "component.h"
#include "input.h"

class Mesh;
class WorldComponent;

class WorldEditor : public Component, public InputListener
{
public:
	WorldEditor();
	~WorldEditor();

	virtual void init(json descr) override;
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void render() const override;
	virtual void debugUI() override;
	virtual void debugUISpecial() override;

	virtual Component* clone() const override;
	virtual const std::string& getName() const override { return "WorldEditor"; }

	virtual void onButtonPressed(int button) override;
	virtual void onButtonReleased(int button) override;
	virtual void onKeyPressed(int key) override;
	virtual void onKeyReleased(int key) override;
	virtual void onMouseWheel(int wheel) override;

private:
	int m_selectedTile;
	float m_cursorDist, m_cursorDistPrecision;
	ivec3 m_target;
	Mesh* m_cursorMesh;
	Transform m_cursorTransform;
	WorldComponent* m_world;
	bool m_mousePressed;
	bool m_isUIVisible;
};
