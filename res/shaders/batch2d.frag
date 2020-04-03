#version 400 core

out vec4 FragColor;

in vec2 v_texCoord;
in vec3 v_color;
in float v_texUnit;

const int MAX_TEXTURE_UNITS = 8;

uniform sampler2D u_textures[MAX_TEXTURE_UNITS];

void main()
{
    int index = int(v_texUnit);
    FragColor = texture(u_textures[index], v_texCoord) + vec4(v_color, 0.0f);
}