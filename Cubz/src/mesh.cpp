#include <glad.h>
#include <fstream>

#include "vec.h"
#include "mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <obj_loader\tiny_obj_loader.h>

Mesh::Mesh() : m_shader(NULL)
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

	std::string path = descr["obj"];
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::attrib_t attrib;
	std::string err;
	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, ("resources/" + path).c_str());
	m_vertex = new vec3[4]{ vec3(0, 0, 0), vec3(1, 0, 0), vec3(1, 1, 0), vec3(0.5f, 0.5f, 0) };
	unsigned int indices[3] = { 0, 1, 2 };

	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		//glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float) * 3, 0, GL_STATIC_DRAW);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(float) * 3, m_vertex);
		glBufferData(GL_ARRAY_BUFFER, attrib.vertices.size() * sizeof(float) * 3, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, attrib.vertices.size() * sizeof(float) * 3, attrib.vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[0].mesh.indices.size() * sizeof(unsigned int), shapes[0].mesh.indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glGenBuffers(1, &m_vboId);

	m_vertexCount = shapes[0].mesh.indices.size();

	glBindVertexArray(m_vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_shader = Shader::getShader(descr["shader"]);
}

void Mesh::load(const std::string& path)
{
	
}

void Mesh::render()
{
	glBindVertexArray(m_vaoId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
	glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
