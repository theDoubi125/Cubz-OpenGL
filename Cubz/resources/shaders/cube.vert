#version 150 core

in vec3 in_Vertex;
in vec2 in_texCoord;

out vec2 texCoord;

uniform mat4 mvp;

void main()
{
    // Position finale du vertex

    gl_Position = mvp * vec4(in_Vertex, 1.0);
	texCoord = in_texCoord;
}
