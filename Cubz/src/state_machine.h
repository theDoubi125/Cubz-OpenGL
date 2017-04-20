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

	virtual void onPushed() {}
	virtual void onEnterState() {}
	virtual void onOtherStatePushed() {}
	virtual void onExitState() {}
	virtual void update(float deltaTime) {}

	void pushState(State<T>* state)
	{
		StateMachine<T> &machine = m_entity->getStateMachine();
		machine.pushState(state);
	}

	void popState()
	{
		StateMachine<T> &machine = m_entity->getStateMachine();
		machine.popState();
	}

protected:
	T* m_entity;
};

template <typename T>
class StateMachine
{
public:
	StateMachine(State<T>* initState)
	{
		m_states.push(initState);
		initState->onPushed();
		initState->onEnterState();
	}

	~StateMachine()
	{
		while (!m_states.empty())
		{
			delete m_states.top();
			m_states.pop();
		}
	}

	void pushState(State<T>* state)
	{
		if (!m_states.empty())
		{
			m_states.top()->onOtherStatePushed();
		}
		state->onPushed();
		state->onEnterState();
		m_states.push(state);
	}

	void changeState(State<T>* state)
	{
		State<T*> toPop = m_states.top();
		m_states.pop();
		toPop->onExitState();
		delete toPop;
		state->onPushed();
		m_states.push(state);
	}

	void popState()
	{
		State<T>* state = m_states.top();
		m_states.pop();
		state->onExitState();
		delete state;
		if (m_states.size() == 0)
		{
			throw std::exception("Empty state stack");
		}
		m_states.top()->onEnterState();
	}

	void update(float deltaTime)
	{
		m_states.top()->update(deltaTime);
	}

private:
	std::stack<State<T>*> m_states;
};

#endif
