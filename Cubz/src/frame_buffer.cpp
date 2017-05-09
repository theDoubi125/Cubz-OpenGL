#include <glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include "entity.h"

#include "frame_buffer.h"

RenderTarget::RenderTarget(ivec2 size) : m_size(size)
{
	glGenTextures(1, &m_targetTexture);
	glBindTexture(GL_TEXTURE_2D, m_targetTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &m_frameBuffer);
	glGenRenderbuffers(1, &m_renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_size.x, m_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_targetTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTarget::~RenderTarget()
{
	glDeleteRenderbuffers(1, &m_renderBuffer);
	glDeleteFramebuffers(1, &m_frameBuffer);
	glDeleteTextures(1, &m_targetTexture);
}

void RenderTarget::renderEntities(const std::vector<Entity*>& entities)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	for (int i = 0; i < entities.size(); i++)
	{
		entities.at(i)->render();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}