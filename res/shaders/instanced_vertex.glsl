#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexture;

uniform vec2 offsets[100];
uniform float u_screenWidth;
uniform float u_screenHeight;

out vec2 fTexture;

void main()
{
    vec2 offset = offsets[gl_InstanceID];
    float x = mix(-1.0, 1.0, aPos.x + offset.x / u_screenWidth);
    float y = mix(1.0, -1.0, aPos.y + offset.y / u_screenHeight);
    gl_Position = vec4(x, y, 0.0, 1.0);
    fTexture = aTexture;
}