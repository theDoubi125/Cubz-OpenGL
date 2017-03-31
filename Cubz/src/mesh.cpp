#include <glad.h>
#include <fstream>

#include "vec.h"
#include "mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <obj_loader\tiny_obj_loader.h>

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

void Mesh::init(json descr)
{
	m_vertexCount = 3;
	m_vertex = new vec2[m_vertexCount];// vertices[] = { 0.0, 0.0,  1, 0.0,   1, 1 };
	m_vertex[0] = vec2(0, 0);
	m_vertex[1] = vec2(1, 0);
	m_vertex[2] = vec2(1, 1);
	glGenBuffers(1, &m_vboId);
	glGenVertexArrays(1, &m_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(vec2), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertexCount * sizeof(vec2), m_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::load(const std::string& path)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::attrib_t attrib;
	std::string err;
	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str());

}

void Mesh::render()
{
	glBindVertexArray(m_vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
