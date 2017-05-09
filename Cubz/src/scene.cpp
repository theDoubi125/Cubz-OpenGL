#include <glad.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <json.hpp>
#include <fstream>
#include <imgui.h>

#include "shader.h"
#include "scene.h"
#include "entity.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities[i];
	}
}

void Scene::init(json descr)
{
	for (json::iterator it = descr.begin(); it != descr.end(); it++)
	{
		Entity* entity = new Entity();
		entity->init(*it);
		addEntity(entity);
	}
}

void Scene::start()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); it++)
		(*it)->start();
}

void Scene::update(float deltaTime)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if(m_paused)
			m_entities[i]->updatePaused(deltaTime);
		else
			m_entities[i]->update(deltaTime);
	}
}

void Scene::debugUI()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (ImGui::TreeNode(m_entities[i]->getName().c_str()))
		{
			m_entities[i]->debugUI();
			ImGui::TreePop();
		}
	}
}

void Scene::debugUISpecial()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->debugUISpecial();
	}
}

void Scene::addEntity(Entity* entity)
{
	m_entities.push_back(entity);
	m_entitiesByName[entity->getName()] = entity;
	entity->setScene(*this);
}

void Scene::removeEntity(Entity* entity)
{
	m_entitiesByName.erase(entity->getName());
	for (auto it = m_entities.begin(); it != m_entities.end(); it++)
	{
		if (*it == entity)
		{
			delete *it;
			m_entities.erase(it);
		}
	}
}

void Scene::render() const
{
	glEnable(GL_DEPTH_TEST);
	for (int i = 0; i < m_entities.size(); i++)
		m_entities[i]->render();
}

Entity* Scene::getEntity(const std::string& name) const
{
	return m_entitiesByName.at(name);
}

Entity* Scene::getEntity(const std::string& name)
{
	return m_entitiesByName.at(name);
}
