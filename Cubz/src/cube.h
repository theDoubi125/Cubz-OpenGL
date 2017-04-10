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

	virtual void onKeyPressed(int key);
	virtual void onKeyReleased(int key);

private:
	StateMachine<Entity>* m_stateMachine;
	ivec2 m_inputVec;
	bool m_rightInput, m_leftInput, m_upInput, m_downInput;
};

#endif
