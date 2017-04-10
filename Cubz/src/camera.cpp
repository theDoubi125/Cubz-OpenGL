#include "vec.h"
#include "camera.h"
#include "entity.h"

Camera* Camera::m_activeCamera = NULL;

void Camera::init(json descr)
{
	if (descr["active"].get<bool>())
	{
		m_activeCamera = this;
	}
}

Component* Camera::clone() const
{
	Camera* result = new Camera();
	result->m_entity = m_entity;
	return result;
}

const std::string& Camera::getName() const
{
	return "Camera";
}

const mat4& Camera::getViewMatrix() const
{
	mat4 result = inverse(m_entity->transform().transformMatrix());
	result[0].z *= -1;
	result[1].z *= -1;
	result[2].z *= -1;
	result[3].z *= -1;
	return result;
}

void Camera::activate()
{
	m_activeCamera = this;
}


void FreeCamera::init(json descr)
{

}

void FreeCamera::update(float deltaTime)
{
	vec3 vec = vec3(m_inputVec.x * deltaTime * 1, 0, m_inputVec.y * deltaTime * 1);
	m_entity->transform().translate(vec);
}

void FreeCamera::onKeyPressed(int key)
{
	switch (key)
	{
	case GLFW_KEY_UP:
		m_inputVec.y = 1;
		m_upInput = true;
		break;
	case GLFW_KEY_DOWN:
		m_inputVec.y = -1;
		m_downInput = true;
		break;
	case GLFW_KEY_LEFT:
		m_inputVec.x = -1;
		m_leftInput = true;
		break;
	case GLFW_KEY_RIGHT:
		m_inputVec.x = 1;
		m_rightInput = true;
		break;
	}
}

void FreeCamera::onKeyReleased(int key)
{
	switch (key)
	{
	case GLFW_KEY_UP:
		m_upInput = false;
		m_inputVec.y = 0;
		if (m_downInput)
			m_inputVec.y = -1;
		break;
	case GLFW_KEY_DOWN:
		m_downInput = false;
		m_inputVec.y = 0;
		if (m_upInput)
			m_inputVec.y = 1;
		break;
	case GLFW_KEY_LEFT:
		m_leftInput = false;
		m_inputVec.x = 0;
		if (m_rightInput)
			m_inputVec.y = 1;
		break;
	case GLFW_KEY_RIGHT:
		m_rightInput = false;
		m_inputVec.x = 0;
		if (m_leftInput)
			m_inputVec.y = -1;
		break;
	}
}

void FreeCamera::onMouseMove(int x, int y)
{
	m_mousePos.x += x - m_lastMousePos.x;
	m_mousePos.y += y - m_lastMousePos.y;
	
}

Component* FreeCamera::clone() const
{
	return new FreeCamera();
}

const std::string& FreeCamera::getName() const
{
	return "FreeCamera";
}