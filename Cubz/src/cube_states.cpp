#include <glad/glad.h>
#include <imgui.h>
#include <fstream>
#include "cube_states.h"

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
