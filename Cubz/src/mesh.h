#ifndef MESH_INCLUDED
#define MESH_INCLUDED

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "vec.h"
#include "shader.h"
#include <json.hpp>

#define PART_COUNT_MAX 10
#define MAX_VERTEX_COUNT 2000

class Mesh
{
public:
	virtual ~Mesh();

	void initData(int partCount);
	void setData(int partId, Shader* shader, int vertexCount, float* vertex, float* uv, float* normals, GLuint drawType = GL_STATIC_DRAW);
	void render(mat4 transformMatrix, vec3 lightDir) const;
	void render(mat4 transformMatrix, int partId) const;
	void renderFinal() const;

	int getPartCount() const;

	void bindShader(int partId) const;

	void setColor(vec3 color);

private:
	GLuint m_vbos[PART_COUNT_MAX];
	GLuint m_vaos[PART_COUNT_MAX];
	Shader* m_shaders[PART_COUNT_MAX];
	int m_vertexCount[PART_COUNT_MAX];
	int m_partCount;

	GLuint m_modelAttribs[PART_COUNT_MAX];
	GLuint m_viewAttribs[PART_COUNT_MAX];
	GLuint m_projectionAttribs[PART_COUNT_MAX];
	GLuint m_lightDirAttribs[PART_COUNT_MAX];

	GLuint m_colorAttribs[PART_COUNT_MAX];

	vec3 m_colors[PART_COUNT_MAX];
};

class LoadedMesh : public Mesh
{
public:
	LoadedMesh();
	virtual ~LoadedMesh();

	void init(json descr);
};

#endif MESH_INCLUDED
