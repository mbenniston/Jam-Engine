#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 color;
layout(location = 3) in int texUnit;

uniform mat4 u_vp;

out vec2 v_texCoord;
out vec3 v_color;
out int v_texUnit;

void main()
{
    gl_Position = u_vp * vec4(position, 0.0f, 1.0f);
    v_texCoord = texCoord;
    v_color = color;
    v_texUnit = texUnit;
}