#ifndef TRANSFORM_INCLUDED
#define TRANSFORM_INCLUDED

#include "vec.h"

class Transform
{
public:
	Transform();
	Transform(const vec3& pos, const quat& rot, float scale);
	Transform(const Transform &transform);
	~Transform();

	mat4 transformMatrix() const;

	void setPosition(const vec3& pos);
	void setRotation(const quat& rot);
	void setScale(float scale);

	void translate(const vec3& vec);
	void rotate(const quat& rot);
	void scale(const float scale);

	void lookAt(const vec3& pos);

	const vec3& position() const;
	const quat& rotation() const;
	const float& scale() const;

	vec3& position();
	quat& rotation();
	float& scale();

	vec3 worldToLocal(const vec3& pos);
	vec3 localToWorld(const vec3& pos);

private:
	vec3 m_pos;
	quat m_rot;
	float m_scale;
};

#endif
