#ifndef STATE_MACHINE_INCLUDED
#define STATE_MACHINE_INCLUDED

#include <stack>

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
	virtual void onOtherStatePushed() = 0;
	virtual void onExitState() = 0;
	virtual void onReleaseState() = 0;
private:
	T* m_entity;
};

template <typename T>
class StateMachine
{
public:
	StateMachine(State<T>* initState)
	{
		m_states.push(initState);
	}

	~StateMachine()
	{
		while (!m_states.empty())
		{
			delete m_states.pop();
		}
	}

	void pushState(State<T*> state)
	{
		m_states.top()->onOtherStatePushed();
	}

	void changeState(State<T*> state)
	{

	}

	void popState()
	{

	}

private:
	std::stack<State<T>*> m_states;
};

#endif