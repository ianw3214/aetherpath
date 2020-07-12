#include "background.hpp"

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <random>

#include "game/camera/camera.hpp"

Background::Background()
{
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<int> position_dist(-5000, 5000);
    std::uniform_int_distribution<int> parallax_dist(1, 6);

    for (int i = 0; i < num_stars; ++i)
    {
        const float x = static_cast<float>(position_dist(el));
        const float y = static_cast<float>(position_dist(el));
        const float parallax = static_cast<float>(parallax_dist(el));
        m_stars.push_back(StarInfo{ x, y, parallax });
    }
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

    static Shader shader("res/shaders/instanced_vertex.glsl", "res/shaders/instanced_fragment.glsl");
    shader.setUniform1f("u_screenWidth", (float) Oasis::WindowService::WindowWidth());
    shader.setUniform1f("u_screenHeight", (float) Oasis::WindowService::WindowHeight());
    // static Shader shader("res/shaders/basic_vertex.glsl", "res/shaders/basic_fragment.glsl");
    for (unsigned int i = 0; i < 100; ++i)
    {
        const float x = CameraService::RawToScreenX(m_stars[i].x);
        const float y = CameraService::RawToScreenY(m_stars[i].y);
        shader.setUniform2f("offsets[" + std::to_string(i) + "]", x, y);
    }

    // Bind the texture and draw
    static Oasis::Texture texture("res/sprites/star.png");
	texture.bind();
	shader.bind();
	va.bind();
    
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
}