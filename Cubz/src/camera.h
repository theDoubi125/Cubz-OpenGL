#ifndef CAMERA_INCLUDED
#define CAMERA_INCLUDED

#include "component.h"

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

#endif
