// Version du GLSL

#version 150 core


// Entrée Shader

in vec3 in_Vertex;

uniform mat4 transform;


// Fonction main

void main()
{
    // Position finale du vertex

    gl_Position = vec4(in_Vertex, 1.0);
}
