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
	return m_entity->transform().transformMatrix();
}

void Camera::activate()
{
	m_activeCamera = this;
}
