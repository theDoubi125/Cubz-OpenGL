#ifndef CUBE_INCLUDED
#define CUBE_INCLUDED

#include "component.h"
#include "state_machine.h"
#include "input.h"

class CubeComponent : public Component, public InputListener
{
public:
	CubeComponent();
	~CubeComponent();

	virtual void start() override;
	virtual void init(json descr) override;
	virtual void update(float deltaTime) override;
	virtual Component* clone() const override;
	virtual void render() const override;
	virtual void debugUI() override;
	virtual const std::string& getName() const override;

	StateMachine<CubeComponent>& getStateMachine() { return *m_stateMachine; }
	const StateMachine<CubeComponent>& getStateMachine() const { return *m_stateMachine; }

private:
	StateMachine<CubeComponent>* m_stateMachine;
};

#endif
