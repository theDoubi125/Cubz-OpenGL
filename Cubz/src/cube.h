#ifndef CUBE_INCLUDED
#define CUBE_INCLUDED

#include "component.h"
#include "state_machine.h"
#include "input.h"
#include "vec.h"

class World;

class CubeComponent : public Component, public InputListener
{
public:
	CubeComponent();
	~CubeComponent();

	virtual void start() override;
	virtual void init(json descr) override;
	virtual void update(float deltaTime) override;
	virtual Component* clone() const override;
	virtual void debugUI() override;
	virtual const std::string& getName() const override;

	const ivec3& getCell() const { return m_currentCell; }
	void changeCell(const ivec3 &cellDisp);
	void setCell(const ivec3 &cell);

	void onKeyPressed(int key) override;
	void onKeyReleased(int key) override;

	StateMachine<CubeComponent>& getStateMachine() { return *m_stateMachine; }
	const StateMachine<CubeComponent>& getStateMachine() const { return *m_stateMachine; }

	World& getWorld();

	const ivec2& getInputDir() const;

private:
	StateMachine<CubeComponent>* m_stateMachine;
	World* m_world;
	ivec3 m_currentCell;
	ivec2 m_inputDir;
};

#endif
