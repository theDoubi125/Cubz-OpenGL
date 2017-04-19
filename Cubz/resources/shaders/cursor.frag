// Version du GLSL

#version 150 core


// Sortie Shader

in vec2 texCoord;
out vec4 out_Color;

// Fonction main

void main()
{
    // Couleur finale du pixel

    out_Color = vec4(0, 0, 1.0, 0.5f);
}
