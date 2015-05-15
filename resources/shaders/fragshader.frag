#version 130

in vec2 fragPosition;
in vec4 fragColor;
in vec2 fragUV;

out vec4 color;

uniform float time;
uniform sampler2D testTexture;

void main(void)
{
    vec4 textureColor = texture(testTexture, fragUV);
    color = textureColor;
}

