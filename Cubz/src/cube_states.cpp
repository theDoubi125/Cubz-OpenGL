#include <glad/glad.h>
#include <imgui.h>
#include <fstream>
#include "cube.h"
#include "state_machine.h"
#include "cube_states.h"
#include "entity.h"

void IdleState::onEnterState()
{
	startListening();
}

void IdleState::onOtherStatePushed()
{
	stopListening();
}

void IdleState::onKeyPressed(int key)
{
	if (key == GLFW_KEY_RIGHT)
	{
		pushState((State<CubeComponent>*)new MovingState(m_entity, ivec2(1, 0)));
	}
	if (key == GLFW_KEY_LEFT)
	{
		pushState((State<CubeComponent>*)new MovingState(m_entity, ivec2(-1, 0)));
	}
	if (key == GLFW_KEY_UP)
	{
		pushState((State<CubeComponent>*)new MovingState(m_entity, ivec2(0, 1)));
	}
	if (key == GLFW_KEY_DOWN)
	{
		pushState((State<CubeComponent>*)new MovingState(m_entity, ivec2(0, -1)));
	}
}



MovingState::MovingState(CubeComponent* entity, ivec2 dir) : State<CubeComponent>(entity), m_dir(dir)
{

}

void MovingState::onPushed()
{

}

void MovingState::onEnterState()
{

}

void MovingState::onOtherStatePushed()
{

}

void MovingState::onExitState()
{

}

void MovingState::update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 1)
	{
		m_entity->getEntity().transform().translate(vec3(m_dir.x * (deltaTime - m_time + 1), 0, m_dir.y * (deltaTime - m_time + 1)));
		popState();
	}
	else
	{
		m_entity->getEntity().transform().translate(vec3(m_dir.x * deltaTime, 0, m_dir.y * deltaTime));
	}
}
