#include "entity.h"
#include "cube.h"
#include "input.h"

CubeComponent::CubeComponent() : Component(), m_stateMachine(NULL)
{
	
}

CubeComponent::~CubeComponent()
{
	delete m_stateMachine;
}

void CubeComponent::init(json descr)
{
	Input::instance.addListener(this);
}

void CubeComponent::update(float deltaTime)
{
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

}

void CubeComponent::render() const
{

}
void CubeComponent::debugUI()
{

}

const std::string& CubeComponent::getName() const
{
	return "Cube";
}

void CubeComponent::onKeyPressed(int key)
{
	if (key == GLFW_KEY_UP)
	{
		m_inputVec.y = 1;
		m_upInput = true;
	}
	if (key == GLFW_KEY_DOWN)
	{
		m_inputVec.y = -1;
		m_downInput = true;
	}
	if (key == GLFW_KEY_LEFT)
	{
		m_inputVec.x = -1;
		m_leftInput = true;
	}
	if (key == GLFW_KEY_RIGHT)
	{
		m_inputVec.x = 1;
		m_rightInput = true;
	}
}

void CubeComponent::onKeyReleased(int key)
{
	if (key == GLFW_KEY_UP)
	{
		m_upInput = false;
		m_inputVec.y = 0;
		if (m_downInput)
			m_inputVec.y = -1;
	}
	if (key == GLFW_KEY_DOWN)
	{
		m_downInput = false;
		m_inputVec.y = 0;
		if (m_upInput)
			m_inputVec.y = 1;
	}
	if (key == GLFW_KEY_LEFT)
	{
		m_leftInput = false;
		m_inputVec.x = 0;
		if (m_rightInput)
			m_inputVec.y = 1;
	}
	if (key == GLFW_KEY_RIGHT)
	{
		m_rightInput = false;
		m_inputVec.x = 0;
		if (m_leftInput)
			m_inputVec.y = -1;
	}
}
