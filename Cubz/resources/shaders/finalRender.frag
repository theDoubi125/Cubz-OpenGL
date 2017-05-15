#version 150 core

in vec2 texCoord;

out vec4 out_Color;

uniform sampler2D text;

void main()
{
	vec4 sum = vec4(0, 0, 0, 1);
	float offset = 1/textureSize(text, 0).x;
	for(int i=-5; i<=5; i++)
	{
		sum += texture(text, texCoord + vec2(offset * i, 0));
	}
    out_Color = sum/11.0;//(texture(text, texCoord) + )/2;
    //out_Color = vec4(offset, 0, 0, 1);
}
