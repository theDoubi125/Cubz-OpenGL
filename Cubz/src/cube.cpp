#include "entity.h"
#include "cube.h"
#include "input.h"
#include "cube_states.h"

CubeComponent::CubeComponent() : Component(), m_stateMachine(NULL)
{
	
}

CubeComponent::~CubeComponent()
{
	delete m_stateMachine;
}

void CubeComponent::init(json descr)
{
	startListening();
	m_stateMachine = new StateMachine<CubeComponent>((State<CubeComponent>*)new IdleState(this));
}

void CubeComponent::update(float deltaTime)
{
	m_stateMachine->update(deltaTime);
	//m_entity->transform().translate(vec3(m_inputVec.x, 0, m_inputVec.y) * deltaTime);
}

Component* CubeComponent::clone() const
{
	CubeComponent* result = new CubeComponent();
	result->m_entity = m_entity;
	return result;
}

void CubeComponent::start()
{
	startListening();
}

void CubeComponent::render() const
{

}
void CubeComponent::debugUI()
{

}

const std::string& CubeComponent::getName() const
{
	return "Cube";
}