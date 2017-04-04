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

	glGenBuffers(1, &m_vboId);
	glGenBuffers(1, &m_elementBufferId);
	glGenVertexArrays(1, &m_vaoId);

	std::string path = descr;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::attrib_t attrib;
	std::string err;
	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, ("resources/" + path).c_str());
	m_vertex = new vec3[attrib.vertices.size()];

	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, attrib.vertices.size() * sizeof(float) * 3, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, attrib.vertices.size() * sizeof(float) * 3, attrib.vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, attrib.vertices.size() * sizeof(unsigned int), attrib.vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_vboId);

	m_vertexCount = attrib.vertices.size() / 3;

	glBindVertexArray(m_vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
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
	m_indicesCount = attrib.vertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, attrib.vertices.size() * sizeof(float) * 3, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, attrib.vertices.size() * sizeof(float) * 3, &attrib.vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::render()
{
	glBindVertexArray(m_vaoId);
	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}
