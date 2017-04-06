#pragma once
#include <string>
#include <json.hpp>
#include "resource_manager.h"
#include "vec.h"

class Shader
{
public:
	Shader();
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	Shader(Shader const& model);
	~Shader();
	GLuint getProgramId() const;
	void load();

	static Shader* getShader(json descr);

protected:
	void compile(GLuint &shader, GLenum type, std::string const &source);


private:
	GLuint m_vertexId;
	GLuint m_fragmentId;
	GLuint m_programId;

	std::string m_vertexPath;
	std::string m_fragmentPath;

	static ResourceManager<Shader> m_shaderManager;
};

class Texture
{
public:
	Texture();
	~Texture();

	void init(ivec2 dim);

	void setPixel(ivec2 pos, vec4 col);

	int textureId() { return m_id; }

private:
	GLuint m_id;
	ivec2 m_dim;
	vec4* m_pixels;
};
