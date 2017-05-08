#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <imgui.h>
#include <fstream>
#include "cube.h"
#include "state_machine.h"
#include "cube_states.h"
#include "entity.h"
#include "world.h"
#include "camera.h"

void IdleState::update(float deltaTime)
{
	ivec3 cell = (ivec3)m_entity->getEntity().transform().position();
	m_entity->setCell(cell);

	const ivec2& inputDir = m_entity->getInputDir();
	vec3 worldDir = Camera::ActiveCamera()->right() * (float)inputDir.x + Camera::ActiveCamera()->forward() * (float)inputDir.y;
	if (abs(worldDir.x) > abs(worldDir.z))
		worldDir.z = 0;
	else worldDir.x = 0;
	ivec3 worldInputDir = (ivec3)worldDir;

	if (worldDir.x > 0)
		worldInputDir.x = 1;
	if (worldDir.x < 0)
		worldInputDir.x = -1;
	if (worldDir.z > 0)
		worldInputDir.z = 1;
	if (worldDir.z < 0)
		worldInputDir.z = -1;

	ivec3 targetCell = m_entity->getCell() + worldInputDir;
	const World& world = m_entity->getWorld();
	if (world.isInBound(m_entity->getCell() + IVEC_DOWN) && world.getTile(m_entity->getCell() + IVEC_DOWN) == 0)
	{
		pushState((State<CubeComponent>*)new FallState(m_entity, 10, 3));
		return;
	}
	if (inputDir.x != 0 || inputDir.y != 0)
	{
		if (world.getTile(targetCell) == 0 && world.getTile(targetCell + IVEC_UP) == 0 && world.getTile(m_entity->getCell() + IVEC_UP) == 0)
		{
			float angle = pi<float>() / 2;
			if (world.getTile(targetCell + IVEC_DOWN) == 0 && world.getTile(targetCell + worldInputDir + IVEC_DOWN) == 0 && world.getTile(targetCell + worldInputDir) == 0 && targetCell.y > 0)
				angle *= -2;
			pushState((State<CubeComponent>*)new RollState(m_entity, ((vec3)worldInputDir + VEC_DOWN) * 0.5f, angleAxis(-angle, cross((vec3)worldInputDir, VEC_UP)), 1, inputDir));
			return;
		}
		else if (world.getTile(targetCell) == 1 && world.getTile(targetCell + IVEC_UP) == 0 && world.getTile(m_entity->getCell() + IVEC_UP) == 0
			&& world.getTile(m_entity->getCell() + IVEC_UP * 2) == 0 && world.getTile(m_entity->getCell() - worldInputDir + IVEC_UP) == 0 && world.getTile(m_entity->getCell() - worldInputDir) == 0)
		{
			pushState((State<CubeComponent>*)new RollState(m_entity, ((vec3)worldInputDir + VEC_UP) * 0.5f, angleAxis(pi<float>(), cross((vec3)worldInputDir, VEC_UP)), 1, inputDir));
			return;
		}
	}
}

RollState::RollState(CubeComponent* entity, vec3 rotationCenter, quat rotation, float speed, ivec2 inputDir) : State<CubeComponent>(entity)
	, m_rotationCenter(rotationCenter), m_rotation(rotation), m_speed(speed), m_rotationAngle(angle(rotation))
	, m_startRotation(entity->getEntity().transform().rotation()), m_startPosition(entity->getEntity().transform().position())
	, m_inputDir(inputDir), m_isReversed(false)
{

}

void RollState::update(float deltaTime)
{
	const ivec2& inputDir = m_entity->getInputDir();
	float dirDot = dot((vec2)inputDir, (vec2)m_inputDir);
	if ((!m_isReversed && dirDot < 0) || (m_isReversed && dirDot > 0))
		m_isReversed = !m_isReversed;
	Transform& transform = m_entity->getEntity().transform();
	m_time += deltaTime * m_speed / m_rotationAngle * pi<float>() * (m_isReversed ? -1 : 1);
	quat currentRotation = slerp(m_startRotation, cross(m_rotation, m_startRotation), m_time < 1 ? m_time : 1);
	quat currentRotation2 = slerp(angleAxis(0.0f, VEC_UP), m_rotation, m_time < 1 ? m_time : 1);
	transform.setPosition(m_startPosition + m_rotationCenter - m_rotationCenter * inverse(currentRotation2));
	transform.setRotation(currentRotation);
	if (m_time < 0)
	{
		m_time = 0;
		popState();
	}
	if (m_time > 1)
	{
		m_time = 1;
		popState();
	}
}

void RollState::onExitState()
{
	ivec3 cell = (ivec3)m_entity->getEntity().transform().position();
	m_entity->setCell(cell);
	Transform& transform = m_entity->getEntity().transform();
	quat currentRotation = slerp(m_startRotation, cross(m_rotation, m_startRotation), m_time < 1 ? m_time : 1);
	quat currentRotation2 = slerp(angleAxis(0.0f, VEC_UP), m_rotation, m_time < 1 ? m_time : 1);
	transform.setPosition(m_startPosition + m_rotationCenter - m_rotationCenter * inverse(currentRotation2));
	transform.setRotation(currentRotation);
}

FallState::FallState(CubeComponent* entity, float gravity, float maxSpeed) : State<CubeComponent>(entity), m_gravity(gravity), m_maxSpeed(maxSpeed), m_speed(0)
{

}

void FallState::update(float deltaTime)
{
	m_speed += m_gravity * deltaTime;
	if (m_speed > m_maxSpeed)
		m_speed = m_maxSpeed;
	Transform& transform = m_entity->getEntity().transform();
	const World& world = m_entity->getWorld();
	transform.translate(VEC_DOWN * m_speed * deltaTime);
	ivec3 cell = (ivec3)round(transform.position() + VEC_DOWN * 0.5f);
	if (world.getTile(cell) != 0 || !world.isInBound(cell))
	{
		transform.setPosition(cell + IVEC_UP);
		popState();
	}
}

void FallState::onExitState()
{
}
