#version 150 core

uniform vec3 lightDir;

in vec2 texCoord;
in vec3 normal;

out vec4 out_Color;

void main()
{
	float ratio = dot(normalize(vec3(1, 1, 1)), normalize(normal));
    out_Color = vec4(texCoord, 1.0, 1.0) * (clamp(ratio, 0, 1) + 0.5);
}
