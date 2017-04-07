#include <glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

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
		glBufferData(GL_ARRAY_BUFFER, attrib.vertices.size() * sizeof(float) * 5, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, attrib.vertices.size() * sizeof(float) * 3, attrib.vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, attrib.vertices.size() * sizeof(float) * 3, attrib.vertices.size() * sizeof(float) * 2, attrib.texcoords.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[0].mesh.indices.size() * sizeof(unsigned int), shapes[0].mesh.indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_vertexCount = shapes[0].mesh.indices.size();

	glBindVertexArray(m_vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(attrib.vertices.size() * sizeof(float) * 3));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_shader = Shader::getShader(descr["shader"]);
	m_projectionAttrib = glGetUniformLocation(m_shader->getProgramId(), "projection");
	m_transformAttrib = glGetUniformLocation(m_shader->getProgramId(), "transform");
}

void Mesh::load(const std::string& path)
{
	
}

void Mesh::render(mat4 transformMatrix, mat4 projectionMatrix)
{
	glUseProgram(m_shader->getProgramId());
	int shaderId = m_shader->getProgramId();
	glUniformMatrix4fv(m_projectionAttrib, 1, GL_FALSE, value_ptr(projectionMatrix));
	glUniformMatrix4fv(m_transformAttrib, 1, GL_FALSE, value_ptr(transformMatrix));
	glBindVertexArray(m_vaoId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
	glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}
