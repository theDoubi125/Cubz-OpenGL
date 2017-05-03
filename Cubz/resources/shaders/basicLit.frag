#version 150 core

uniform vec3 lightDir;
uniform vec3 cubeColor;

in vec2 texCoord;
in vec3 normal;

out vec4 out_Color;

void main()
{
	float ratio = dot(normalize(vec3(0.5, 1, 0.3)), normalize(normal));
    out_Color = vec4(cubeColor, 1.0) * (clamp(ratio, 0.1, 1));
}
