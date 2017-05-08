#pragma once

#include "state_machine.h"
#include "cube.h"
#include "input.h"
#include "vec.h"

class IdleState : State<CubeComponent>
{
public:
	IdleState(CubeComponent* entity) : State<CubeComponent>(entity)
	{

	}

	virtual void update(float deltaTime) override;
};

class RollState : State<CubeComponent>
{
public:
	RollState(CubeComponent* entity, vec3 rotationCenter, quat rotation, float speed, ivec2 inputDir);

	virtual void onExitState() override;
	virtual void update(float deltaTime) override;

private:
	float m_time, m_speed, m_rotationAngle;
	vec3 m_rotationCenter;
	vec3 m_startPosition;
	quat m_rotation;
	quat m_startRotation;
	ivec2 m_inputDir;

	bool m_isReversed;
};

class FallState : State<CubeComponent>
{
public:
	FallState(CubeComponent* entity, float gravity, float maxSpeed);

	virtual void onExitState() override;
	virtual void update(float deltaTime) override;

private:
	float m_speed, m_gravity, m_maxSpeed;
};