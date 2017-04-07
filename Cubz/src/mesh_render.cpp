#include <glad.h>
#include <GLFW\glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh.h"
#include "mesh_render.h"
#include "entity.h"

MeshManager MeshRenderer::m_meshManager;

MeshRenderer::MeshRenderer()
{

}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::registerMeshes()
{
	//Mesh* mesh = new Mesh();
	//mesh->init();
	//registerMesh("Test", mesh);
}

void MeshRenderer::init(json descr)
{
	std::cout << descr.dump(0) << std::endl;
	std::string resourceName = descr["mesh"]["obj"];
	if (!m_meshManager.hasResource(resourceName))
	{
		Mesh *mesh = new Mesh();
		mesh->init(descr["mesh"]);
		m_meshManager.registerResource(resourceName, mesh);
	}
	m_mesh = m_meshManager.getResource(resourceName);
}

void MeshRenderer::start()
{

}

void MeshRenderer::update(float deltaTime)
{

}

void MeshRenderer::render() const
{
	mat4 projectionMatrix = perspective(70.0, (double)800 / 600, 0.1, 100.0);
	m_mesh->render(m_entity->transform().transformMatrix(), projectionMatrix);
}

void MeshRenderer::debugUI()
{

}

Component* MeshRenderer::clone() const
{
	MeshRenderer* result = new MeshRenderer();
	result->m_entity = m_entity;
	result->m_mesh = m_mesh;
	return result;
}
