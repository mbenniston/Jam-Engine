#version 400 core

out vec4 FragColor;

uniform sampler2D texture0, fontAtlas;
uniform vec3 u_color;

in vec2 v_texCoord;

subroutine vec4 TexSampleMethod();
subroutine uniform TexSampleMethod u_texSampleMethod;

subroutine(TexSampleMethod)
vec4 DefaultTexSample()
{
    return texture(texture0, v_texCoord);
}

subroutine(TexSampleMethod)
vec4 GrayScaleSample()
{
    float r = texture(fontAtlas, v_texCoord).r;
    if(r < 0.5f) discard;

    return vec4(u_color * r, r);
}

void main()
{
    FragColor = u_texSampleMethod();
}