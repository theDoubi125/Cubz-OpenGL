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

	vec3 colors[] = { vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), vec3(1, 1, 0), vec3(1, 0, 1), vec3(0, 1, 1), vec3(1, 1, 1) };

	for (int i = 0; i < 8; i++)
	{
		m_colors[i] = colors[i];
	}

	glGenBuffers(partCount, m_vbos);
	glGenVertexArrays(partCount, m_vaos);

	memset(m_vertexCount, 0, partCount * sizeof(int));
	memset(m_shaders, NULL, partCount);
}

void Mesh::setData(int partId, Shader* shader, int vertexCount, float* vertex, float* uv, float* normals, GLuint drawType)
{
	m_shaders[partId] = shader;
	m_modelAttribs[partId] = glGetUniformLocation(m_shaders[partId]->getProgramId(), "model");
	m_viewAttribs[partId] = glGetUniformLocation(m_shaders[partId]->getProgramId(), "view");
	m_projectionAttribs[partId] = glGetUniformLocation(m_shaders[partId]->getProgramId(), "projection");
	m_colorAttribs[partId] = glGetUniformLocation(m_shaders[partId]->getProgramId(), "cubeColor");
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[partId]);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 8, 0, drawType);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * sizeof(float) * 3, vertex);
		glBufferSubData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 3, vertexCount * sizeof(float) * 2, uv);
		glBufferSubData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 5, vertexCount * sizeof(float) * 3, normals);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_vertexCount[partId] = vertexCount;
	glBindVertexArray(m_vaos[partId]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[partId]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexCount * sizeof(float) * 3));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexCount * sizeof(float) * 5));
			glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::render(mat4 transformMatrix) const
{
	for (int i = 0; i < m_partCount; i++)
	{
		glUseProgram(m_shaders[i]->getProgramId());
		mat4 viewMatrix = Camera::ActiveCamera()->getViewMatrix();
		mat4 projectionMatrix = Camera::ActiveCamera()->getProjectionMatrix();
		glUniformMatrix4fv(m_modelAttribs[i], 1, GL_FALSE, value_ptr(transformMatrix));
		glUniformMatrix4fv(m_viewAttribs[i], 1, GL_FALSE, value_ptr(viewMatrix));
		glUniformMatrix4fv(m_projectionAttribs[i], 1, GL_FALSE, value_ptr(projectionMatrix));
		glUniform3f(m_colorAttribs[i], m_colors[i].x, m_colors[i].y, m_colors[i].z);
		glBindVertexArray(m_vaos[i]);
		glDrawArrays(GL_TRIANGLES, 0, m_vertexCount[i]);
		glBindVertexArray(0);
	}
	glUseProgram(0);
}


void Mesh::render(mat4 transformMatrix, int partId) const
{
	mat4 viewMatrix = Camera::ActiveCamera()->getViewMatrix();
	mat4 projectionMatrix = Camera::ActiveCamera()->getProjectionMatrix();
	glUniformMatrix4fv(m_modelAttribs[partId], 1, GL_FALSE, value_ptr(transformMatrix));
	glUniformMatrix4fv(m_viewAttribs[partId], 1, GL_FALSE, value_ptr(viewMatrix));
	glUniformMatrix4fv(m_projectionAttribs[partId], 1, GL_FALSE, value_ptr(projectionMatrix));
	glUniform3f(m_colorAttribs[partId], m_colors[partId].x, m_colors[partId].y, m_colors[partId].z);
	glBindVertexArray(m_vaos[partId]);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount[partId]);
	glBindVertexArray(0);
}

int Mesh::getPartCount() const
{
	return m_partCount;
}

void Mesh::bindShader(int partId) const
{
}

void Mesh::setColor(vec3 color)
{
	for (int i = 0; i < m_partCount; i++)
		m_colors[i] = color;
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
	float normals[MAX_VERTEX_COUNT * 3];
	for (int i = 0; i < vertexCount; i++)
	{
		int vertexId = 3 * indices[i].vertex_index;
		int uvId = 2 * indices[i].texcoord_index;
		int normalId = 3 * indices[i].normal_index;
		vertex[i * 3] = attrib.vertices[vertexId];
		vertex[i * 3 + 1] = attrib.vertices[vertexId + 1];
		vertex[i * 3 + 2] = attrib.vertices[vertexId + 2];
		uv[i * 2] = attrib.texcoords[uvId];
		uv[i * 2 + 1] = attrib.texcoords[uvId + 1];
		normals[i * 3] = attrib.normals[normalId];
		normals[i * 3 + 1] = attrib.normals[normalId + 1];
		normals[i * 3 + 2] = attrib.normals[normalId + 2];
	}

	Shader* shader = Shader::getShader(descr["shader"]);
	initData(1);
	setData(0, shader, vertexCount, vertex, uv, normals);

	vec3 color;
	json colorDescr = descr["color"];
	color.r = colorDescr[0];
	color.g = colorDescr[1];
	color.b = colorDescr[2];
	setColor(color);
}