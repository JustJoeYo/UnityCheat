#pragma once

auto DrawUI() -> void
{
    if (true && show) {
        ImVec2 CatNipPos;

        ImGui::SetNextWindowSize({ 630, 410 });
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
        ImGui::Begin("Friends vs Friends", nullptr, ImGuiWindowFlags_NoDecoration); {
            auto draw = ImGui::GetWindowDrawList();

            auto pos = ImGui::GetWindowPos();
            auto size = ImGui::GetWindowSize();

            CatNipPos = pos;

            ImGuiStyle style = ImGui::GetStyle();

            draw->AddRect(ImVec2(pos.x + 1, pos.y + 1), ImVec2(pos.x + size.x - 1, pos.y + size.y - 1), ImColor(1.0f, 1.0f, 1.0f, 0.1f), style.WindowRounding, ImDrawFlags_RoundCornersLeft); // outline entire thing
            // draw->AddLine(ImVec2(pos.x + 60, pos.y + 2), ImVec2(pos.x + 60, pos.y + size.y - 2), ImColor(1.0f, 1.0f, 1.0f, 0.08f)); // line seperating icons vs content
            draw->AddLine(ImVec2(pos.x + 279, pos.y + 42), ImVec2(pos.x + 383, pos.y + 42), ImColor(1.0f, 1.0f, 1.0f, 0.08f), 1.75f); // line under cheat name

            
            }
        }
        ImGui::End();
        ImGui::PopStyleVar();
}