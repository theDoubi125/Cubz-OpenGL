#include <glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "entity.h"
#include "mesh_render.h"

Entity::Entity() : m_name("")
{

}

Entity::~Entity()
{

}

ComponentFactory Entity::m_componentFactory;

void Entity::registerComponent(const std::string& name, Component* model)
{
	m_componentFactory.registerInstance(name, model);
}

void Entity::registerComponents()
{
	registerComponent("Test", new TestComponent());
	registerComponent("MeshRenderer", new MeshRenderer());
}

void Entity::init(json descr)
{
	for (auto it = descr.begin(); it != descr.end(); it++)
	{
		std::string propertyName = it.key();
		if (propertyName.compare("name") == 0)
		{
			m_name = it->get<std::string>();
		}
		else if (propertyName.compare("components") == 0)
		{
			for (auto compIt = it->begin(); compIt != it->end(); compIt++)
			{
				addComponent(compIt.key(), *compIt);
			}
		}
	}
}

void Entity::start()
{
	for (auto it = m_components.begin(); it != m_components.end(); it++)
	{
		it->second->start();
	}
}

void Entity::update(float deltaTime)
{
	for (auto it = m_components.begin(); it != m_components.end(); it++)
	{
		it->second->update(deltaTime);
	}
}

void Entity::render() const
{
	for (auto it = m_components.begin(); it != m_components.end(); it++)
	{
		it->second->render();
	}
}

void Entity::debugUI()
{
	for (auto it = m_components.begin(); it != m_components.end(); it++)
	{
		if (ImGui::TreeNode(it->first.c_str()))
		{
			it->second->debugUI();
			ImGui::TreePop();
		}
	}
}

const std::string& Entity::getName() const
{
	return m_name;
}

void Entity::addComponent(Component* component)
{
	if (component == NULL)
	{
		throw std::exception("Error : tried to add a NULL component");
	}
	const std::string& name = component->getName();
	if (m_components.count(name) > 0)
	{
		delete m_components[name];
	}
	m_components[name] = component;
}

void Entity::addComponent(const std::string& name, json descr)
{
	Component* component = m_componentFactory.createInstance(name);
	component->init(descr);
	m_components[name] = component;
}

void Entity::removeComponent(Component* component)
{
	auto it = m_components.find(component->getName());
	if (it != m_components.end())
	{
		delete it->second;
		m_components.erase(it);
	}
}

void Entity::removeComponent(const std::string& name)
{
	auto it = m_components.find(name);
	if (it != m_components.end())
	{
		delete it->second;
		m_components.erase(it);
	}
}

Component* Entity::getComponent(const std::string& name)
{
	auto it = m_components.find(name);
	if (it == m_components.end())
		return NULL;
	else return it->second;
}

Transform& Entity::transform()
{
	return m_transform;
}

const Transform& Entity::transform() const
{
	return m_transform;
}