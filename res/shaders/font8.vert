#version 330 core

layout(location = 0) in vec2 position;
layout(location = 0) in vec2 texCoord;

uniform mat4 u_m, u_vp;
uniform vec2 u_texScale, u_texTrans;

out vec2 v_texCoord;

void main()
{
    v_texCoord = u_texScale * (texCoord + u_texTrans);
    gl_Position = u_vp * u_m * vec4(position, 0.0f, 1.0f);
}