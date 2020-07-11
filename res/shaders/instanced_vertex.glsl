#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexture;

out vec2 fTexture;

uniform vec2 offsets[100];

void main()
{
    vec2 offset = offsets[gl_InstanceID];
    gl_Position = vec4(aPos + offset, 0.0, 1.0);
    fTexture = aTexture;
}