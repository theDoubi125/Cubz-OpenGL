#include <glad.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <imgui.h>

#include "component.h"
#include "factory.h"

Component::Component() : m_entity(NULL)
{

}

Component::~Component()
{

}

void Component::setEntity(Entity* entity)
{
	m_entity = entity;
}

TestComponent::TestComponent() : m_time(0)
{

}

TestComponent::~TestComponent()
{

}

void TestComponent::init(json descr)
{

}

void TestComponent::start()
{

}

void TestComponent::update(float deltaTime)
{
	m_time += deltaTime;
}

void TestComponent::render() const
{

}

void TestComponent::debugUI()
{

}

Component* TestComponent::clone() const
{
	return new TestComponent();
}

const std::string& TestComponent::getName() const
{
	return "Test";
}
