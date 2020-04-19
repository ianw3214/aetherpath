#include "debugLayer.hpp"

#include "game/game.hpp"
#include "game/gameLayer/gameService.hpp"
#include "game/alertLayer/alertService.hpp"

#include "imgui.h"
void DebugLayer::Init() 
{
    Oasis::ImGuiWrapper::AddWindowFunction([=](){
        ImGui::SetCurrentContext(Oasis::ImGuiWrapper::GetContext());
        static bool show = true;
        ImGui::Begin("DEBUG", &show, ImGuiWindowFlags_MenuBar);

        // Camera debug (Technically numbers go a lot higher, but limit it for debug purposes)
        ImGui::SliderFloat("Camera x", &(Camera::GetCamera()->m_x), -1000.f, 1000.f);
        ImGui::SliderFloat("Camera y", &(Camera::GetCamera()->m_y), -1000.f, 1000.f);
        ImGui::SliderFloat("Camera scale", &(Camera::GetCamera()->m_scale), 0.1f, 5.f);

        // Mess with gameplay settings debug
        ImGui::SliderFloat("seconds_per_tick", &(GameService::s_settings.m_seconds_per_tick), 0.001f, 1.f);
        ImGui::SliderFloat("seconds_per_day", &(GameService::s_settings.m_seconds_per_day), 1.f, 5.f * 60.f);

        // Test win/lose the game
        if (ImGui::Button("WIN GAME"))
        {
            AlertService::Win();
        }
        if (ImGui::Button("LOSE GAME"))
        {
            AlertService::Lose();
        }

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
