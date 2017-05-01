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

void IdleState::update(float deltaTime)
{
	ivec3 cell = (ivec3)m_entity->getEntity().transform().position();
	m_entity->setCell(cell);

	const ivec2& inputDir = m_entity->getInputDir();
	const ivec3 worldInputDir = ivec3(inputDir.x, 0, inputDir.y);
	ivec3 targetCell = m_entity->getCell() + worldInputDir;
	vec3 movementDir(inputDir.x, 0, inputDir.y);
	int tile = m_entity->getWorld().getTile(targetCell);
	const World& world = m_entity->getWorld();
	if (world.isInBound(m_entity->getCell() + IVEC_DOWN) && world.getTile(m_entity->getCell() + IVEC_DOWN) == 0)
	{
		pushState((State<CubeComponent>*)new FallState(m_entity, 10, 3));
		return;
	}
	if (inputDir.x != 0 || inputDir.y != 0)
	{
		if (!world.isInBound(targetCell) || tile == 0)
		{
			pushState((State<CubeComponent>*)new RollState(m_entity, (movementDir + VEC_DOWN) * 0.5f, angleAxis(-pi<float>() / 2, cross(movementDir, VEC_UP)), 1));
			return;
		}
		else if (world.getTile(targetCell + IVEC_UP) == 0 && world.getTile(m_entity->getCell()) == 0)
		{
			pushState((State<CubeComponent>*)new RollState(m_entity, (movementDir + VEC_UP) * 0.5f, angleAxis(pi<float>(), cross(movementDir, VEC_UP)), 1));
			return;
		}
	}
}

RollState::RollState(CubeComponent* entity, vec3 rotationCenter, quat rotation, float speed) : State<CubeComponent>(entity)
	, m_rotationCenter(rotationCenter), m_rotation(rotation), m_speed(speed), m_rotationAngle(angle(rotation))
	, m_startRotation(entity->getEntity().transform().rotation()), m_startPosition(entity->getEntity().transform().position())
{

}

void RollState::update(float deltaTime)
{
	Transform& transform = m_entity->getEntity().transform();
	m_time += deltaTime * m_speed / m_rotationAngle * pi<float>();
	if (m_time > 1)
		deltaTime -= m_time - 1;
	quat currentRotation = slerp(m_startRotation, cross(m_rotation, m_startRotation), m_time < 1 ? m_time : 1);
	quat currentRotation2 = slerp(angleAxis(0.0f, VEC_UP), m_rotation, m_time < 1 ? m_time : 1);
	transform.setPosition(m_startPosition + m_rotationCenter - m_rotationCenter * inverse(currentRotation2));
	transform.setRotation(currentRotation);
	if (m_time > 1)
	{
		popState();
	}
}

void RollState::onExitState()
{
	ivec3 cell = (ivec3)m_entity->getEntity().transform().position();
	m_entity->setCell(cell);
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