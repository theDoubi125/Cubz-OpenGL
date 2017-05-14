#version 150 core

in vec2 in_Vertex;
in vec2 in_texCoord;
in vec3 in_normal;
out vec2 texCoord;


void main()
{
    gl_Position = vec4(in_Vertex, 0, 1.0);
	texCoord = in_Vertex.xy;
}
