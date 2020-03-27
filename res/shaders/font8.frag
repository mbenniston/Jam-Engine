#version 330 core

out vec4 FragColor;

uniform vec3 u_color;
uniform sampler2D texture0;

in vec2 v_texCoord;

void main()
{
    float r = texture(texture0, v_texCoord).r;
    FragColor = vec4(u_color * r, r);
}