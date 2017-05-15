#include <glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include "vec.h"
#include "image_effect.h"
#include "shader.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

ImageEffect::ImageEffect()
{

}

void ImageEffect::init()
{
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);

	float data[]{ -1, -1,  1, 1,  1, -1,  -1, -1,  -1, 1,  1, 1 };

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_shader = new Shader("resources/shaders/finalRender.vert", "resources/shaders/finalRender.frag");
	m_shader->load();
}

void ImageEffect::render(GLuint textureId) const
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(m_shader->getProgramId());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}