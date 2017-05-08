#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#include <json.hpp>
#include "component.h"
#include "factory.h"
#include "transform.h"
#include "scene.h"

class Entity
{
public:
	Entity();
	~Entity();

	void init(json descr);
	void start();
	void update(float deltaTime);
	void updatePaused(float deltaTime);
	void render() const;

	void debugUI();
	void debugUISpecial();

	const std::string& getName() const;

	void addComponent(Component* component);
	void addComponent(const std::string& name, json descr);
	void removeComponent(const std::string& name);
	void removeComponent(Component* component);
	Component* getComponent(const std::string& name);

	static void registerComponent(const std::string& name, Component* model);
	static void registerComponents();

	Transform& transform();
	const Transform& transform() const;

	Scene& getScene() { return *m_scene; }
	void setScene(Scene& scene) { m_scene = &scene; }

private:
	std::string m_name;
	std::map<std::string, Component*> m_components; 
	static ComponentFactory m_componentFactory;
	Transform m_transform;
	Scene* m_scene;
};

#endif
