#include <glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "entity.h"

#include "render_target.h"

RenderTarget::RenderTarget()
{
	
}

void RenderTarget::init(ivec2 size)
{
	m_size = size;

	float *pixels = new float[size.x * size.y * 3];
	memset(pixels, 0, sizeof(float) * size.x * size.y * 3);
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			pixels[(i + j * size.x) * 3] = 1.0f;
			pixels[(i + j * size.x) * 3 + 1] = 0.5f;
		}
	}
	

	glGenFramebuffers(1, &m_frameBuffer);
	glGenRenderbuffers(1, &m_renderBuffer);
	glGenTextures(1, &m_targetTexture);

	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
	glBindTexture(GL_TEXTURE_2D, m_targetTexture);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_size.x, m_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_FLOAT, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_targetTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

RenderTarget::~RenderTarget()
{
	glDeleteRenderbuffers(1, &m_renderBuffer);
	glDeleteFramebuffers(1, &m_frameBuffer);
	glDeleteTextures(1, &m_targetTexture);
}

void RenderTarget::renderEntities(const std::vector<Entity*>& entities) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < entities.size(); i++)
	{
		entities.at(i)->render();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint RenderTarget::getTargetTexture() const
{
	return m_targetTexture;
}