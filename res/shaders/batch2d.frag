#version 330 core

out vec4 FragColor;

in vec2 v_texCoord;
in vec3 v_color;
in int v_texUnit;

void main()
{
    FragColor = vec4(v_color, 1.0f);
}