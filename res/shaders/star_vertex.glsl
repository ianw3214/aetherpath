#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexture;

uniform vec2 offsets[100];
uniform float parallaxes[100];

uniform float u_screenWidth;
uniform float u_screenHeight;
uniform float u_scale;
uniform float u_cameraX;
uniform float u_cameraY;

out vec2 fTexture;

void main()
{
    vec2 offset = offsets[gl_InstanceID];
    float parallax = parallaxes[gl_InstanceID];
    // Stars aren't affected by camera scale
    float x_raw = (offset.x - u_cameraX) / parallax * u_scale + u_screenWidth / 2;
    float y_raw = (offset.y - u_cameraY) / parallax * u_scale + u_screenHeight / 2;
    // Have the stars be _slightly_ affected by parallax distance
    float scaled_x = aPos.x / (parallax / 3.0);
    float scaled_y = aPos.y / (parallax / 3.0);
    float x = mix(-1.0, 1.0, (scaled_x + x_raw) / u_screenWidth);
    float y = mix(1.0, -1.0, (scaled_y + y_raw) / u_screenHeight);
    gl_Position = vec4(x, y, 0.0, 1.0);
    fTexture = aTexture;
}