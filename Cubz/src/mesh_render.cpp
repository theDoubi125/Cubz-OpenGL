#include <glad.h>
#include <GLFW\glfw3.h>

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
	std::string resourceName = descr["mesh"]["obj"];
	if (!m_meshManager.hasResource(resourceName))
	{
		LoadedMesh *mesh = new LoadedMesh();
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
	m_mesh->render(m_entity->transform().transformMatrix(), vec3(1, 0.5f, 0.3f));
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
