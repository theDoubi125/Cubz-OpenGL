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

	GLuint m_vboId, m_vaoId, m_elementBufferId;
	vec3* m_vertex;
	int m_vertexCount, m_indicesCount;
};

#endif MESH_INCLUDED
