#include <glad.h>
#include <GLFW\glfw3.h>
#include <imgui.h>

#include "entity.h"
#include "vec.h"
#include "world_editor.h"
#include "mesh.h"
#include "world.h"

WorldEditor::WorldEditor() : m_cursorMesh(NULL), m_mousePressed(false)
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
	m_cursorDistPrecision = 1;
	m_cursorTransform.setScale(1.01f);
	startListening();
}

void WorldEditor::start()
{
	m_world = (WorldComponent*)m_entity->getScene().getEntity("World")->getComponent("World");
}

void WorldEditor::update(float deltaTime)
{
	m_target = m_entity->transform().position() + (VEC_FORWARD * m_cursorDist) * inverse(m_entity->transform().rotation());
	m_cursorTransform.setPosition(m_target);
	if (m_mousePressed && m_world->world().getTile(m_target) != m_selectedTile)
	{
		m_world->world().setTile(m_target, m_selectedTile);
		m_world->updateRender();
	}
}

void WorldEditor::render() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_cursorMesh->render(m_cursorTransform.transformMatrix());
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void WorldEditor::debugUI()
{
	ImGui::DragInt("Tile", &m_selectedTile, 0.01f, 0, 9);
}

Component* WorldEditor::clone() const
{
	WorldEditor* result = new WorldEditor();
	return result;
}

void WorldEditor::onButtonPressed(int button)
{
	if(button == 0)
		m_mousePressed = true;
}

void WorldEditor::onButtonReleased(int button)
{
	if (button == 0)
		m_mousePressed = false;
}

void WorldEditor::onKeyPressed(int key)
{
	if (key == GLFW_KEY_F)
	{
		m_entity->getScene().setGamePaused(true);
	}
}

void WorldEditor::onKeyReleased(int key)
{
	if (key == GLFW_KEY_F)
	{
		m_entity->getScene().setGamePaused(false);
	}
}

void WorldEditor::onMouseWheel(int wheel)
{
	m_cursorDist += (float)wheel * m_cursorDistPrecision;
}
