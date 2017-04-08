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
	auto indices = shapes[0].mesh.indices;
	m_vertexCount = indices.size();
	m_vertex = new vec3[m_vertexCount];
	m_uvs = new vec2[m_vertexCount];
	for (int i = 0; i < m_vertexCount; i++)
	{
		int vertexId = 3*indices[i].vertex_index;
		int uvId = 3 * indices[i].texcoord_index;
		m_vertex[i] = vec3(attrib.vertices[vertexId], attrib.vertices[vertexId+1], attrib.vertices[vertexId+2]);
		m_uvs[i] = vec2(attrib.vertices[uvId], attrib.vertices[uvId+1]);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(float) * 5, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertexCount * sizeof(float) * 3, m_vertex);
		glBufferSubData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(float) * 3, m_vertexCount * sizeof(float) * 2, m_uvs);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_vertexCount = shapes[0].mesh.indices.size();

	glBindVertexArray(m_vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_vertexCount * sizeof(float) * 3));
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
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray(0);
	glUseProgram(0);
}
