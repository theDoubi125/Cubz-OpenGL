#include <imgui.h>
#include "vec.h"
#include "camera.h"
#include "entity.h"
#include <glm/gtc/matrix_transform.hpp>

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

const mat4& Camera::getProjectionMatrix() const
{
	return perspective(70.0, (double)800 / 600, 0.1, 100.0);
}

void Camera::activate()
{
	m_activeCamera = this;
}


void FreeCamera::init(json descr)
{
	m_verticalInput = 0;
	m_sensitivity = descr["sensitivity"].get<float>();
	m_walkSpeed = descr["walkSpeed"].get<float>();
	m_verticalSpeed = descr["verticalSpeed"].get<float>();
}

void FreeCamera::start()
{
	startListening();
}

void FreeCamera::update(float deltaTime)
{
	vec3 vec = vec3(m_inputVec.x, 0, m_inputVec.y) * inverse(m_entity->transform().rotation());
	vec.y = 0;
	if(vec != vec3(0, 0, 0))
		vec = normalize(vec) * m_walkSpeed;
	vec += vec3(0, m_verticalInput * m_verticalSpeed, 0);
	m_entity->transform().translate(vec * deltaTime);
}

void FreeCamera::onKeyPressed(int key)
{
	switch (key)
	{
	case GLFW_KEY_W:
		m_inputVec.y = 1;
		m_upInput = true;
		break;
	case GLFW_KEY_S:
		m_inputVec.y = -1;
		m_downInput = true;
		break;
	case GLFW_KEY_A:
		m_inputVec.x = -1;
		m_leftInput = true;
		break;
	case GLFW_KEY_D:
		m_inputVec.x = 1;
		m_rightInput = true;
		break;
	case GLFW_KEY_LEFT_SHIFT:
		m_verticalInput = 1;
		break;
	case GLFW_KEY_LEFT_CONTROL:
		m_verticalInput = -1;
		break;
	}
}

void FreeCamera::onKeyReleased(int key)
{
	switch (key)
	{
	case GLFW_KEY_W:
		m_upInput = false;
		m_inputVec.y = 0;
		if (m_downInput)
			m_inputVec.y = -1;
		break;
	case GLFW_KEY_S:
		m_downInput = false;
		m_inputVec.y = 0;
		if (m_upInput)
			m_inputVec.y = 1;
		break;
	case GLFW_KEY_A:
		m_leftInput = false;
		m_inputVec.x = 0;
		if (m_rightInput)
			m_inputVec.x = 1;
		break;
	case GLFW_KEY_D:
		m_rightInput = false;
		m_inputVec.x = 0;
		if (m_leftInput)
			m_inputVec.x = -1;
		break;
	case GLFW_KEY_LEFT_SHIFT:
		m_verticalInput = 0;
		break;
	case GLFW_KEY_LEFT_CONTROL:
		m_verticalInput = 0;
		break;
	}
}

void FreeCamera::onButtonPressed(int button)
{
	if (button == 1)
	{
		m_leftButtonInput = true;
		m_dragMousePos = m_mousePos;
	}
}

void FreeCamera::onButtonReleased(int button)
{
	if (button == 1)
		m_leftButtonInput = false;
}

void FreeCamera::onMouseMove(int x, int y)
{
	m_mousePos.x = x;
	m_mousePos.y = y;
	if (m_leftButtonInput)
	{
		ivec2 diff = ivec2(x, y) - m_lastMousePos;
		m_viewAngles += m_sensitivity * (vec2)(diff);
		m_entity->transform().rotation() = quat(vec3(m_viewAngles.y, m_viewAngles.x, 0));
	}
	m_lastMousePos = ivec2(x, y);
}

Component* FreeCamera::clone() const
{
	return new FreeCamera();
}

const std::string& FreeCamera::getName() const
{
	return "FreeCamera";
}

void FreeCamera::debugUI()
{
	vec3 vec = vec3(m_inputVec.x, 0, m_inputVec.y) * quat(vec3(-m_mousePos.y / 100.0f, m_mousePos.x / 100.0f, 0));
	vec.y = 0;
	vec = normalize(vec);

	ImGui::InputFloat3("position", &vec.x);
}
