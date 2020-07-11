#version 330 core
out vec4 FragColor;
  
uniform sampler2D u_Texture;
in vec2 fTexture;

void main()
{
    FragColor = texture(u_Texture, fTexture);
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}