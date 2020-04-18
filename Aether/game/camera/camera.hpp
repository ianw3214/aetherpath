#pragma once
#include "oasis.h"

////////////////////////////////////////////////////////////////////////////////////////
class Camera : public Oasis::GameStateLayer
{
public:
    // Let the debug layer access camera members directly
    friend class DebugLayer;
public:
    // Global access to the camera
    static Oasis::Reference<Camera> GetCamera() { return s_camera;}
public:
    Camera();

    virtual void Init() override;
    virtual void Close() override;

    virtual bool HandleEvent(const Oasis::Event& event) override;
    virtual void Update()  override;

    int GetX() const { return m_x; }
    int GetY() const { return m_y; }
    float GetScale() const { return m_scale; }
private:
    static Oasis::Reference<Camera> s_camera;

    // Center position of the camera
    int m_x;
    int m_y;
    // How zoomed in/out the user is with the camera
    float m_scale;
};