#include "Rendering/Renderer.h"
#include <imgui.h>
#include <cmath>
#include <cstdio>

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::RenderSimulationScene(const std::vector<SimulatedEntity>& entities, const RenderSettings& settings) {
    ImGui::Begin("Simulation & Live Preview");

    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
    if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
    if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImU32 bgColor = IM_COL32(20, 24, 33, 255);
    if (settings.enableSkyChanger) {
        int r = (int)(settings.skyColor[0] * 255);
        int g = (int)(settings.skyColor[1] * 255);
        int b = (int)(settings.skyColor[2] * 255);
        bgColor = IM_COL32(r, g, b, 255);
    }
    draw_list->AddRectFilled(canvas_p0, canvas_p1, bgColor);
    draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(60, 70, 90, 255));

    ImVec2 center(canvas_p0.x + canvas_sz.x * 0.5f, canvas_p0.y + canvas_sz.y * 0.5f);
    for (float x = -canvas_sz.x * 0.5f; x < canvas_sz.x * 0.5f; x += 40.0f) {
        draw_list->AddLine(ImVec2(center.x + x, canvas_p0.y), ImVec2(center.x + x, canvas_p1.y), IM_COL32(35, 42, 55, 100));
    }
    for (float y = -canvas_sz.y * 0.5f; y < canvas_sz.y * 0.5f; y += 40.0f) {
        draw_list->AddLine(ImVec2(canvas_p0.x, center.y + y), ImVec2(canvas_p1.x, center.y + y), IM_COL32(35, 42, 55, 100));
    }

    for (const auto& ent : entities) {
        ImVec2 screenPos(center.x + ent.posX * 1.2f, center.y + ent.posZ * 0.8f);

        if (screenPos.x < canvas_p0.x || screenPos.x > canvas_p1.x || screenPos.y < canvas_p0.y || screenPos.y > canvas_p1.y)
            continue;

        ImU32 entColor = ent.isTeamMate ? 
            IM_COL32((int)(settings.teamColor[0]*255), (int)(settings.teamColor[1]*255), (int)(settings.teamColor[2]*255), 255) :
            IM_COL32((int)(settings.enemyColor[0]*255), (int)(settings.enemyColor[1]*255), (int)(settings.enemyColor[2]*255), 255);

        if (settings.enableChams) {
            int cr = (int)(settings.chamsColor[0] * 255);
            int cg = (int)(settings.chamsColor[1] * 255);
            int cb = (int)(settings.chamsColor[2] * 255);
            entColor = IM_COL32(cr, cg, cb, 255);
        }

        float radius = 14.0f;
        draw_list->AddCircleFilled(screenPos, radius, entColor);
        draw_list->AddCircle(screenPos, radius, IM_COL32(255, 255, 255, 200), 12, 1.5f);

        if (settings.enableESP) {
            if (settings.box2D) {
                ImVec2 bMin(screenPos.x - 20.0f, screenPos.y - 35.0f);
                ImVec2 bMax(screenPos.x + 20.0f, screenPos.y + 15.0f);
                draw_list->AddRect(bMin, bMax, entColor, 0.0f, 0, 1.2f);
            }

            if (settings.names) {
                draw_list->AddText(ImVec2(screenPos.x - 25.0f, screenPos.y - 52.0f), IM_COL32(240, 240, 240, 255), ent.name.c_str());
            }

            if (settings.healthBars) {
                ImVec2 hbStart(screenPos.x - 26.0f, screenPos.y - 35.0f);
                ImVec2 hbEnd(screenPos.x - 23.0f, screenPos.y + 15.0f);
                draw_list->AddRectFilled(hbStart, hbEnd, IM_COL32(50, 50, 50, 200));
                float healthPct = ent.health / 100.0f;
                ImVec2 hpCurr(screenPos.x - 26.0f, screenPos.y + 15.0f - (50.0f * healthPct));
                draw_list->AddRectFilled(hpCurr, hbEnd, IM_COL32(40, 220, 60, 255));
            }
        }

        if (settings.enableTracers) {
            ImVec2 origin(center.x, canvas_p1.y);
            if (settings.tracerOrigin == 1) origin = center;
            else if (settings.tracerOrigin == 2) origin = ImVec2(center.x, canvas_p0.y);

            int tr = (int)(settings.tracerColor[0] * 255);
            int tg = (int)(settings.tracerColor[1] * 255);
            int tb = (int)(settings.tracerColor[2] * 255);
            draw_list->AddLine(origin, screenPos, IM_COL32(tr, tg, tb, 200), settings.tracerThickness);
        }
    }

    if (settings.noFlash && settings.flashAlpha > 0.0f) {
        ImU32 flashColor = IM_COL32(255, 255, 255, (int)(settings.flashAlpha * 255));
        draw_list->AddRectFilled(canvas_p0, canvas_p1, flashColor);
    }

    ImGui::End();
}

void Renderer::RenderRadarOverlay(const std::vector<SimulatedEntity>& entities, const RenderSettings& settings) {
    if (!settings.enableRadar) return;

    ImGui::SetNextWindowSize(ImVec2(220, 220), ImGuiCond_FirstUseEver);
    ImGui::Begin("2D Radar Overlay", nullptr, ImGuiWindowFlags_NoCollapse);

    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
    if (canvas_sz.x < 150.0f) canvas_sz.x = 150.0f;
    if (canvas_sz.y < 150.0f) canvas_sz.y = 150.0f;
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(15, 18, 25, 240));
    draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(80, 90, 110, 255), 4.0f);

    ImVec2 center(canvas_p0.x + canvas_sz.x * 0.5f, canvas_p0.y + canvas_sz.y * 0.5f);
    draw_list->AddCircleFilled(center, 5.0f, IM_COL32(255, 255, 255, 255));

    for (const auto& ent : entities) {
        ImVec2 rPos(center.x + (ent.posX * 0.35f * settings.radarZoom), center.y + (ent.posZ * 0.35f * settings.radarZoom));
        if (rPos.x >= canvas_p0.x && rPos.x <= canvas_p1.x && rPos.y >= canvas_p0.y && rPos.y <= canvas_p1.y) {
            ImU32 col = ent.isTeamMate ? IM_COL32(50, 200, 50, 255) : IM_COL32(220, 50, 50, 255);
            draw_list->AddCircleFilled(rPos, 4.0f, col);
        }
    }

    ImGui::End();
}

void Renderer::RenderESPDrawings(const std::vector<SimulatedEntity>&, const RenderSettings&) {}
