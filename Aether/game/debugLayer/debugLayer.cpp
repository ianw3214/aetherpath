#include "debugLayer.hpp"

#include "game/game.hpp"

#include "imgui.h"
void DebugLayer::Init() 
{
    Oasis::ImGuiWrapper::AddWindowFunction([=](){
        ImGui::SetCurrentContext(Oasis::ImGuiWrapper::GetContext());
        static bool show = true;
        ImGui::Begin("DEBUG", &show, ImGuiWindowFlags_MenuBar);

        /*
        // General debug info
        auto player = Game::GetEntityLayer()->GetPlayer();
        ImGui::Text("Player Position: (%.2f, %.2f)", player->GetX(), player->GetY());

        // Draw flags
        ImGui::Checkbox("Draw collisions", &m_drawPhysics);
        ImGui::Checkbox("Draw health", &m_drawHealth);
        */
        // Camera debug (Technically numbers go a lot higher, but limit it for debug purposes)
        ImGui::SliderFloat("Camera x", &(Camera::GetCamera()->m_x), -1000.f, 1000.f);
        ImGui::SliderFloat("Camera y", &(Camera::GetCamera()->m_y), -1000.f, 1000.f);
        ImGui::SliderFloat("Camera scale", &(Camera::GetCamera()->m_scale), 0.1f, 5.f);
        ImGui::End();   
    });
}

void DebugLayer::Close() 
{

}

bool DebugLayer::HandleEvent(const Oasis::Event& event) 
{
    return false;
}

void DebugLayer::Update()  
{

}
