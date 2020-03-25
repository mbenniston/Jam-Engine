#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_vp, u_m;

out vec2 v_texCoord;

void main()
{
    gl_Position = u_vp * u_m * vec4(position, 0.0, 1.0f);
    v_texCoord = texCoord;
}