#include "background.hpp"

#include <glm/glm.hpp>
#include <GL/glew.h>

Background::Background()
{

}

void Background::Render() const
{
    // TODO: Cache the sprite
    static Oasis::Sprite sprite(path);
    sprite.SetDimensions(1280.f, 960.f);
    sprite.SetPos(0.f, 0.f);
    Oasis::Renderer::DrawSprite(&sprite);

    DrawStars();
}

void Background::DrawStars() const
{
    float positions[32] = {
		-0.05f, -0.05f, 0.f, 0.f,
		-0.05f,  0.05f, 0.f, 1.f,
        0.05f,  0.05f, 1.f, 1.f,

        -0.05f, -0.05f, 0.f, 0.f,
		0.05f, -0.05f, 1.f, 0.f,
		0.05f,  0.05f, 1.f, 1.f
	};

    VertexArray		va;
	VertexBuffer	vb(positions, sizeof(float) * 32);
	// Specify the layout of the buffer data
	VertexBufferLayout layout;
	layout.pushFloat(2);
	layout.pushFloat(2);
	va.addBuffer(vb, layout);

    float translations[200];
    int index = 0;
    float offset = 0.1f;
    for (int y =  -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            translations[index++] = (float)x / 10.f + offset;
			translations[index++] = (float)y / 10.f + offset;
        }
    }
    static Shader shader("res/shaders/instanced_vertex.glsl", "res/shaders/instanced_fragment.glsl");
    // static Shader shader("res/shaders/basic_vertex.glsl", "res/shaders/basic_fragment.glsl");
    for (unsigned int i = 0; i < 100; ++i)
    {
        shader.setUniform2f("offsets[" + std::to_string(i) + "]", translations[2 * i], translations[2 * i + 1]);
    }

    // Bind the texture and draw
    static Oasis::Texture texture("res/sprites/star.png");
	texture.bind();
	shader.bind();
	va.bind();
    
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
}