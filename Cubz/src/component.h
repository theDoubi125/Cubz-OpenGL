#ifndef COMPONENT_INCLUDED
#define COMPONENT_INCLUDED

#include "json.hpp"
#include "factory.h"

using json = nlohmann::json;

class Entity;

enum ComponentType
{
	MESH_RENDERER = 0,
	STATE_MACHINE = 1,
	CUBE = 2
};

class Component
{
public:
	Component();
	virtual ~Component();
	virtual void init(json descr) {}
	virtual void start() {}
	virtual void update(float deltaTime) {}
	virtual void render() const {}
	virtual void debugUI() {}
	
	virtual Component* clone() const = 0;

	virtual const std::string& getName() const = 0;

	void setEntity(Entity* entity);

protected:
	Entity* m_entity;
};

class TestComponent : public Component
{
public:
	TestComponent();
	~TestComponent();
	virtual void init(json descr) override;
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void render() const override;
	virtual void debugUI() override;

	virtual Component* clone() const override;
	virtual const std::string& getName() const override;

private:
	float m_time;
};

typedef Factory<std::string, Component> ComponentFactory;

#endif COMPONENT_INCLUDED
