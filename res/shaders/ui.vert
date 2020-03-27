#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_vp, u_m;

out vec2 v_texCoord;

uniform vec2 u_texScale, u_texTrans;

subroutine vec2 TexCoordMethod();
subroutine uniform TexCoordMethod u_texCoordMethod;

subroutine(TexCoordMethod)
vec2 TexAtlasMethod()
{
    return u_texScale * (texCoord + u_texTrans);
}

subroutine(TexCoordMethod)
vec2 DefaultTexMethod()
{
    return texCoord;
}

void main()
{
    gl_Position = u_vp * u_m * vec4(position, 0.0, 1.0f);
    v_texCoord = u_texCoordMethod();
}