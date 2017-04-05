#include "transform.h"

Transform::Transform()
{

}

Transform::Transform(const vec3& pos, const quat& rot, float scale) : m_pos(pos), m_rot(rot), m_scale(scale)
{

}

Transform::Transform(const Transform &transform) : m_pos(transform.position()), m_rot(transform.rotation()), m_scale(transform.scale())
{

}

Transform::~Transform()
{

}

mat4 Transform::transformMatrix() const
{
	return toMat4(m_rot);
}

void Transform::setPosition(const vec3& pos)
{
	m_pos = pos;
}

void Transform::setRotation(const quat& rot)
{
	m_rot = rot;
}

void Transform::setScale(float scale)
{
	m_scale = scale;
}

void Transform::translate(const vec3& vec)
{
	m_pos += vec;
}

void Transform::rotate(const quat& rot)
{
	m_rot *= rot;
}

void Transform::scale(float scale)
{
	m_scale *= scale;
}

void Transform::lookAt(const vec3& pos)
{

}

const vec3& Transform::position() const
{
	return m_pos;
}

const quat& Transform::rotation() const
{
	return m_rot;
}

const float Transform::scale() const
{
	return m_scale;
}
