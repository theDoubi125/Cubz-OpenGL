#include <glad.h>
#include <GLFW\glfw3.h>

#include "mesh.h"
#include "mesh_render.h"

MeshManager MeshRenderer::m_meshManager;

MeshRenderer::MeshRenderer()
{

}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::registerMesh(const std::string& name, Mesh* mesh)
{
	m_meshManager.registerResource(name, mesh);
}

void MeshRenderer::registerMeshes()
{
	//Mesh* mesh = new Mesh();
	//mesh->init();
	//registerMesh("Test", mesh);
}

void MeshRenderer::init(json descr)
{
	m_mesh = m_meshManager.getResource(descr["mesh"]);
}

void MeshRenderer::start()
{

}

void MeshRenderer::update(float deltaTime)
{

}

void MeshRenderer::render() const
{
	m_mesh->render();
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
