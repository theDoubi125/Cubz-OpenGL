#include <glad.h>
#include <GLFW\glfw3.h>

#include "entity.h"
#include "vec.h"
#include "world_editor.h"
#include "mesh.h"
#include "world.h"

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
	m_world = (WorldComponent*)m_entity->getScene().getEntity("World")->getComponent("World");
}

void WorldEditor::update(float deltaTime)
{
	m_target = m_entity->transform().position() + (VEC_FORWARD * m_cursorDist) * inverse(m_entity->transform().rotation());
	m_cursorTransform.setPosition(m_target);
	if (m_world->world().getTile(m_target) == 0)
	{
		m_world->world().setTile(m_target, 1);
		m_world->updateRender();
	}
}

void WorldEditor::render() const
{
	m_cursorMesh->render(m_cursorTransform.transformMatrix());
}

void WorldEditor::debugUI()
{

}

Component* WorldEditor::clone() const
{
	WorldEditor* result = new WorldEditor();
	return result;
}
