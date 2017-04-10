#ifndef CAMERA_INCLUDED
#define CAMERA_INCLUDED

#include "component.h"
#include "input.h"

class Camera : public Component
{
public:
	virtual void init(json descr) override;

	virtual Component* clone() const override;
	virtual const std::string& getName() const override;

	const mat4& getViewMatrix() const;

	void activate();

	static Camera* ActiveCamera()
	{
		return m_activeCamera;
	}

private:
	static Camera* m_activeCamera;
};

class FreeCamera : public Component, public InputListener
{
public:
	virtual void init(json descr) override;
	virtual void update(float deltaTime) override;

	virtual Component* clone() const override;
	virtual const std::string& getName() const override;

	virtual void onKeyPressed(int key) override;
	virtual void onKeyReleased(int key) override;
	virtual void onMouseMove(int x, int y) override;

private:
	ivec2 m_inputVec;
	bool m_rightInput, m_leftInput, m_upInput, m_downInput;
	ivec2 m_mousePos, m_lastMousePos;
};

#endif
