#version 130

in vec2 vertPosition;
in vec4 vertColor;
in vec2 vertUV;

out vec2 fragPosition;
out vec4 fragColor;
out vec2 fragUV;

uniform mat4 P;

void main(void)
{
    gl_Position = P * vec4(vertPosition, 0.0, 1.0);
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    fragPosition = vertPosition;
    fragColor = vertColor;
    fragUV = vertUV;
}

