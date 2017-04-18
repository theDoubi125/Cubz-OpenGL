#include <glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include "vec.h"
#include "mesh.h"
#include "camera.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <obj_loader\tiny_obj_loader.h>

Mesh::~Mesh()
{
	glDeleteBuffers(m_partCount, m_vbos);
	glDeleteVertexArrays(m_partCount, m_vaos);
}

void Mesh::initData(int partCount)
{
	m_partCount = partCount;

	glGenBuffers(partCount, m_vbos);
	glGenVertexArrays(partCount, m_vaos);

	memset(m_vertexCount, 0, partCount * sizeof(int));
	memset(m_shaders, NULL, partCount);
}

void Mesh::setData(int partId, Shader* shader, int vertexCount, float* vertex, float* uv, GLuint drawType)
{
	m_shaders[partId] = shader;
	m_mvpAttribs[partId] = glGetUniformLocation(m_shaders[partId]->getProgramId(), "mvp");
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[partId]);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 5, 0, drawType);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * sizeof(float) * 3, vertex);
		glBufferSubData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 3, vertexCount * sizeof(float) * 2, uv);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_vertexCount[partId] = vertexCount;
	glBindVertexArray(m_vaos[partId]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[partId]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexCount * sizeof(float) * 3));
			glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

LoadedMesh::LoadedMesh()
{

}

LoadedMesh::~LoadedMesh()
{

}

void LoadedMesh::init(json descr)
{
	std::string path = descr["obj"];
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::attrib_t attrib;
	std::string err;
	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, ("resources/" + path).c_str());
	auto indices = shapes[0].mesh.indices;
	int vertexCount = indices.size();
	float vertex[MAX_VERTEX_COUNT * 3];
	float uv[MAX_VERTEX_COUNT * 2];
	for (int i = 0; i < vertexCount; i++)
	{
		int vertexId = 3 * indices[i].vertex_index;
		int uvId = 2 * indices[i].texcoord_index;
		vertex[i * 3] = attrib.vertices[vertexId];
		vertex[i * 3 + 1] = attrib.vertices[vertexId + 1];
		vertex[i * 3 + 2] = attrib.vertices[vertexId + 2];
		uv[i * 2] = attrib.texcoords[uvId];
		uv[i * 2 + 1] = attrib.texcoords[uvId + 1];
	}

	Shader* shader = Shader::getShader(descr["shader"]);
	initData(1);
	setData(0, shader, vertexCount, vertex, uv);
}

void Mesh::render(mat4 transformMatrix) const
{
	for (int i = 0; i < m_partCount; i++)
	{
		glUseProgram(m_shaders[i]->getProgramId());
		int shaderId = m_shaders[i]->getProgramId();
		mat4 viewMatrix = Camera::ActiveCamera()->getViewMatrix();
		mat4 projectionMatrix = Camera::ActiveCamera()->getProjectionMatrix();
		glUniformMatrix4fv(m_mvpAttribs[i], 1, GL_FALSE, value_ptr(projectionMatrix * viewMatrix * transformMatrix));
		glBindVertexArray(m_vaos[i]);
		glDrawArrays(GL_TRIANGLES, 0, m_vertexCount[i]);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}
