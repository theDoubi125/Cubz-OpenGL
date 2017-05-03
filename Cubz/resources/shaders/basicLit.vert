#version 150 core


in vec3 in_Vertex;
in vec2 in_texCoord;
in vec3 in_normal;

out vec2 texCoord;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
	texCoord = in_texCoord;
	vec4 worldNormal = (model * vec4(in_normal, 1.0) - model * vec4(0, 0, 0, 1.0));
	normal = worldNormal.xyz;
	 
}
