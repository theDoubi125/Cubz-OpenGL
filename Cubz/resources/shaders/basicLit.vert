#version 150 core


in vec3 in_Vertex;
in vec2 in_texCoord;
in vec3 in_normal;

out vec2 texCoord;
out vec3 normal;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(in_Vertex, 1.0);
	texCoord = in_texCoord;
	vec4 worldNormal = (mvp * vec4(in_normal, 1.0) - mvp * vec4(0, 0, 0, 1.0));
	normal = worldNormal.xyz;
	 
}
