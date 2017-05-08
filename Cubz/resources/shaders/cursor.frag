#version 150 core

uniform vec3 lightDir;
uniform vec3 cubeColor;

in vec2 texCoord;
in vec3 normal;

out vec4 out_Color;

void main()
{
	float ratio = dot(normalize(lightDir), normalize(normal));
    out_Color = vec4(0, 0, 1.0, 0.5f);
}
