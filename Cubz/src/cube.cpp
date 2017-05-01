#include <glad/glad.h>
#include <imgui.h>

#include "entity.h"
#include "cube.h"
#include "input.h"
#include "cube_states.h"
#include "world.h"

CubeComponent::CubeComponent() : Component(), m_stateMachine(NULL), m_world(NULL), m_currentCell(0, 0, 0)
{
	
}

CubeComponent::~CubeComponent()
{
	delete m_stateMachine;
}

void CubeComponent::init(json descr)
{
	startListening();
	m_stateMachine = new StateMachine<CubeComponent>((State<CubeComponent>*)new IdleState(this));
}

void CubeComponent::update(float deltaTime)
{
	m_stateMachine->update(deltaTime);
	//m_entity->transform().translate(vec3(m_inputVec.x, 0, m_inputVec.y) * deltaTime);
}

Component* CubeComponent::clone() const
{
	CubeComponent* result = new CubeComponent();
	result->m_entity = m_entity;
	return result;
}

void CubeComponent::start()
{
	m_world = &((WorldComponent*)m_entity->getScene().getEntity("World")->getComponent("World"))->world();
	m_currentCell = (ivec3)m_entity->transform().position();
	startListening();
}

void CubeComponent::debugUI()
{
	ImGui::InputInt3("Cell", (int*)&m_currentCell);
}

const std::string& CubeComponent::getName() const
{
	return "Cube";
}

World& CubeComponent::getWorld()
{
	return *m_world;
}

void CubeComponent::changeCell(const ivec3& cellDisp)
{
	m_currentCell += cellDisp;
}

void CubeComponent::setCell(const ivec3& cell)
{
	m_currentCell = cell;
}

void CubeComponent::onKeyPressed(int key)
{
	ivec2 lastInputDir = m_inputDir;
	if (key == GLFW_KEY_RIGHT)
		m_inputDir = ivec2(1, 0);
	if (key == GLFW_KEY_LEFT)
		m_inputDir = ivec2(-1, 0);
	if (key == GLFW_KEY_UP)
		m_inputDir = ivec2(0, 1);
	if (key == GLFW_KEY_DOWN)
		m_inputDir = ivec2(0, -1);
}

void CubeComponent::onKeyReleased(int key)
{
	ivec2 lastInputDir = m_inputDir;
	if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT)
		m_inputDir = ivec2(0, lastInputDir.y);
	if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN)
		m_inputDir = ivec2(lastInputDir.x, 0);
}

const ivec2& CubeComponent::getInputDir() const
{
	return m_inputDir;
}