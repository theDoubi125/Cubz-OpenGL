#include <GLFW/glfw3.h>
#include "input.h"

Input& Input::instance = Input();

InputListener::InputListener()
{

}

InputListener::~InputListener()
{
	Input::instance.removeListener(this);
}

void InputListener::startListening()
{
	Input::instance.addListener(this);
}

void InputListener::stopListening()
{
	Input::instance.removeListener(this);
}

Input::Input()
{
	
}

Input::~Input()
{
	
}

void Input::update()
{
	glfwPollEvents();
}

void Input::addListener(InputListener* listener)
{
	m_listeners.push_back(listener);
}

void Input::removeListener(InputListener* listener)
{
	for (auto it = m_listeners.begin(); it != m_listeners.end(); it++)
	{
		if (*it == listener)
		{
			m_listeners.erase(it);
			return;
		}
	}
}

void Input::onKeyEvent(int key, int event)
{
	int i;
	switch (event)
	{
	case GLFW_PRESS:
		for (i = 0; i < m_listeners.size(); i++)
		{
			m_listeners[i]->onKeyPressed(key);
		}
		break;
	case GLFW_RELEASE:
		for (i = 0; i < m_listeners.size(); i++)
		{
			m_listeners[i]->onKeyReleased(key);
		}
		break;
	case GLFW_REPEAT:
		for (i = 0; i < m_listeners.size(); i++)
		{
			//m_listeners[i]->onKeyReleased(key);
		}
		break;
	}
}

void Input::onMouseMoveEvent(int x, int y)
{
	for (int i = 0; i < m_listeners.size(); i++)
	{
		m_listeners[i]->onMouseMove(x, y);
	}
}

void Input::onButtonEvent(int button, int event)
{
	int i;
	switch (event)
	{
	case GLFW_PRESS:
		for (i = 0; i < m_listeners.size(); i++)
		{
			m_listeners[i]->onButtonPressed(button);
		}
		break;
	case GLFW_RELEASE:
		for (i = 0; i < m_listeners.size(); i++)
		{
			m_listeners[i]->onButtonReleased(button);
		}
		break;
	case GLFW_REPEAT:
		for (i = 0; i < m_listeners.size(); i++)
		{
			//m_listeners[i]->onKeyReleased(key);
		}
		break;
	}
}

void Input::onWheelEvent(int offset)
{
	for (int i = 0; i < m_listeners.size(); i++)
	{
		m_listeners[i]->onMouseWheel(offset);
	}
}
