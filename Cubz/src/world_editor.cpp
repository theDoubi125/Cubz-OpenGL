#include <glad.h>
#include <GLFW\glfw3.h>

#include "entity.h"
#include "vec.h"
#include "world_editor.h"
#include "mesh.h"

WorldEditor::WorldEditor() : m_cursorMesh(NULL)
{

}

WorldEditor::~WorldEditor()
{
	delete m_cursorMesh;
}

void WorldEditor::init(json descr)
{
	m_cursorMesh = new LoadedMesh();
	((LoadedMesh*)m_cursorMesh)->init(descr["mesh"]);
	m_selectedTile = 1;
	m_cursorDist = 5;
}

void WorldEditor::start()
{

}

void WorldEditor::update(float deltaTime)
{
	m_target = m_entity->transform().position() + (VEC_FORWARD * m_cursorDist) * m_entity->transform().rotation();
	m_cursorTransform.setPosition(m_target);
}

void WorldEditor::render() const
{
	m_cursorMesh->render(m_cursorTransform.transformMatrix());
}

void WorldEditor::debugUI()
{

}

void WorldEditor::clone() const
{
	WorldEditor* result = new WorldEditor();
	return result;
}