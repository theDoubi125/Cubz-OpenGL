#pragma once

#include "vec.h"

class Entity;

class RenderTarget
{
public:
	RenderTarget(ivec2 size);
	~RenderTarget();

	void renderEntities(const std::vector<Entity*>& entities);

private:
	GLuint m_frameBuffer;
	GLuint m_targetTexture;
	GLuint m_renderBuffer;
	ivec2 m_size;
};