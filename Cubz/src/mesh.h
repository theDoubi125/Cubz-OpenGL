#ifndef MESH_INCLUDED
#define MESH_INCLUDED

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "vec.h"
#include <json.hpp>

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	void init(json descr);
	void render();

private:
	void load(const std::string& path);

	GLuint m_vboId, m_vaoId;
	vec2* m_vertex;
	vec2* m_triangles;
	int m_vertexCount, m_triangleCount;
};

#endif MESH_INCLUDED
