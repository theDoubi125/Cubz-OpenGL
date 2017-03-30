#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#include <json.hpp>
#include "component.h"
#include "factory.h"


class Entity
{
public:
	Entity();
	~Entity();

	void init(json descr);
	void start();
	void update(float deltaTime);
	void render() const;

	void debugUI();

	const std::string& getName() const;

	void addComponent(Component* component);
	void addComponent(const std::string& name, json descr);
	void removeComponent(const std::string& name);
	void removeComponent(Component* component);
	Component* getComponent(const std::string& name);

	static void registerComponent(const std::string& name, Component* model);
	static void registerComponents();

private:
	std::string m_name;
	std::map<std::string, Component*> m_components; 
	static ComponentFactory m_componentFactory;
};

#endif
