#ifndef STATE_MACHINE_INCLUDED
#define STATE_MACHINE_INCLUDED

#include "component.h"

class Entity;

template<typename T>
class State
{
public:
	State(T* entity)
	{
		m_entity = entity;
	}

	virtual ~State()
	{

	}

	virtual void onInitState() = 0;
	virtual void onEnterState() = 0;
	virtual void onExitState() = 0;
	virtual void onReleaseState() = 0;
private:
	T* m_entity;
};

template <typename T>
class StateMachine
{
public:
	StateMachine();

	~StateMachine();

	void pushState(State<Entity*> state);

	void changeState(State<Entity*> state);

	void popState();
};

#endif