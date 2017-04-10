#ifndef MESH_INCLUDED
#define MESH_INCLUDED

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "vec.h"
#include "shader.h"
#include <json.hpp>

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	void init(json descr);
	void render(mat4 transformMatrix, mat4 projectionMatrix);

private:
	void load(const std::string& path);

	GLuint m_vboId, m_vaoId, m_elementBufferId;
	GLuint m_mvpAttrib;
	vec3* m_vertex;
	vec2* m_uvs;
	int m_vertexCount, m_indicesCount;
	Shader* m_shader;
};

#endif MESH_INCLUDED
