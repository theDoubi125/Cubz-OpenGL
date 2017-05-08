#include <glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <cmath>

#include "entity.h"
#include "mesh_render.h"
#include "cube.h"
#include "camera.h"
#include "world.h"
#include "world_editor.h"

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
	registerComponent("Camera", new Camera());
	registerComponent("FreeCamera", new FreeCamera());
	registerComponent("Test", new TestComponent());
	registerComponent("MeshRenderer", new MeshRenderer());
	registerComponent("Cube", new CubeComponent());
	registerComponent("World", new WorldComponent());
	registerComponent("WorldEditor", new WorldEditor());
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
		else if (propertyName.compare("transform") == 0)
		{
			for (auto transfIt = it->begin(); transfIt != it->end(); transfIt++)
			{
				std::string compName = transfIt.key();
				if (compName.compare("pos") == 0)
				{
					m_transform.position() = vec3(transfIt.value()[0], transfIt.value()[1], transfIt.value()[2]);
				}
				else if (compName.compare("rot") == 0)
				{
					float angle = transfIt.value()["angle"];
					vec3 axis = vec3(transfIt.value()["axis"][0], transfIt.value()["axis"][1], transfIt.value()["axis"][2]);
					m_transform.rotation() = angleAxis(angle, axis);
				}
				else if (compName.compare("scale") == 0)
				{
					m_transform.scale() = transfIt.value().get<float>();
				}
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

void Entity::updatePaused(float deltaTime)
{
	for (auto it = m_components.begin(); it != m_components.end(); it++)
	{
		it->second->updatePaused(deltaTime);
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
	if (ImGui::TreeNode("transform"))
	{
		ImGui::InputFloat3("position", &transform().position().x);
		if (ImGui::TreeNode("rotation"))
		{
			vec3 angles = eulerAngles(transform().rotation());
			vec3 modifiedAngles = angles;
			ImGui::SliderFloat("x", &(modifiedAngles.x), -3.14, 3.14, "%.3f");
			ImGui::SliderFloat("y", &(modifiedAngles.y), -3.14, 3.14, "%.3f");
			ImGui::SliderFloat("z", &(modifiedAngles.z), -3.14, 3.14, "%.3f");

			if (angles != modifiedAngles)
			{
				transform().rotation() = quat(modifiedAngles);
			}

			ImGui::TreePop();
		}
		ImGui::SliderFloat("scale", &(transform().scale()), 0.01, 100, "%.3f");
		ImGui::TreePop();
	}
	for (auto it = m_components.begin(); it != m_components.end(); it++)
	{
		if (ImGui::TreeNode(it->first.c_str()))
		{
			it->second->debugUI();
			ImGui::TreePop();
		}
	}
}

void Entity::debugUISpecial()
{
	for (auto it = m_components.begin(); it != m_components.end(); it++)
	{
		it->second->debugUISpecial();
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
	component->setEntity(this);
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
