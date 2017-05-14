#pragma once

class Shader;

class ImageEffect
{
public:
	ImageEffect();
	void init();

	void render(GLuint textureId) const;

private:
	GLuint m_vao;
	GLuint m_vbo;
	Shader* m_shader;
};