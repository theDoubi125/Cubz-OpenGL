#pragma once

#include "state_machine.h"
#include "cube.h"
#include "input.h"
#include "vec.h"

class IdleState : State<CubeComponent>, public InputListener
{
public:
	virtual void onEnterState() override;
	virtual void onOtherStatePushed() override;

private:
	virtual void onKeyPressed(int key) override;
};

class MovingState : State<CubeComponent>
{
public:
	MovingState(CubeComponent* entity, ivec2 dir);

	virtual void onPushed() override;
	virtual void onEnterState() override;
	virtual void onOtherStatePushed() override;
	virtual void onExitState() override;
	virtual void update(float deltaTime) override;

private:
	ivec2 m_dir;
};
