#pragma once

#include "vec.h"

class Entity;

class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

	void init(ivec2 size);
	void renderEntities(const std::vector<Entity*>& entities) const;

	GLuint getTargetTexture() const;

private:
	GLuint m_frameBuffer;
	GLuint m_targetTexture;
	GLuint m_renderBuffer;
	ivec2 m_size;
};