#include "UI/UIManager.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

UIManager::UIManager() {}
UIManager::~UIManager() {}

void UIManager::Init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 4.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.13f, 0.17f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.15f, 0.20f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.30f, 0.40f, 0.70f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.21f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.28f, 0.38f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.45f, 0.85f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.52f, 0.95f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.38f, 0.75f, 1.00f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void UIManager::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::Render(RenderSettings& settings, Simulation& simulation) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(15, 15), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(340, 860), ImGuiCond_FirstUseEver);
    ImGui::Begin("NovaResearch // CS2 Architecture Demo", nullptr, ImGuiWindowFlags_NoResize);

    ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "SECURITY RESEARCH DASHBOARD");
    ImGui::Separator();

    const char* tabs[] = { "1. ESP", "2. Tracers", "3. Radar", "4. Chams", "5. Sky", "6. World", "7. Misc", "8. Settings" };
    for (int i = 0; i < 8; ++i) {
        if (ImGui::Button(tabs[i], ImVec2(72, 30))) {
            m_ActiveTab = i;
        }
        if ((i + 1) % 4 != 0) ImGui::SameLine();
    }
    ImGui::Separator();

    switch (m_ActiveTab) {
        case 0: RenderESPConfig(settings); break;
        case 1: RenderTracerConfig(settings); break;
        case 2: RenderRadarConfig(settings); break;
        case 3: RenderChamsConfig(settings); break;
        case 4: RenderSkyConfig(settings); break;
        case 5: RenderWorldConfig(settings); break;
        case 6: RenderMiscConfig(settings); break;
        case 7: 
            ImGui::Text("Simulation Controls");
            ImGui::Checkbox("Enable Entity Movement", &simulation.enableMovement);
            ImGui::SliderFloat("Simulation Speed", &simulation.simulationSpeed, 0.1f, 3.0f);
            break;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::RenderESPConfig(RenderSettings& settings) {
    ImGui::Text("ESP Configuration");
    ImGui::Checkbox("Enable ESP", &settings.enableESP);
    ImGui::Separator();
    ImGui::Checkbox("2D Boxes", &settings.box2D);
    ImGui::Checkbox("Skeleton", &settings.skeleton);
    ImGui::Checkbox("Health Bars", &settings.healthBars);
    ImGui::Checkbox("Names", &settings.names);
    ImGui::Checkbox("Distance", &settings.distance);
    ImGui::Checkbox("Weapons", &settings.weapons);
    ImGui::Separator();
    ImGui::ColorEdit3("Box Color", settings.boxColor);
    ImGui::ColorEdit3("Enemy Color", settings.enemyColor);
    ImGui::ColorEdit3("Team Color", settings.teamColor);
}

void UIManager::RenderTracerConfig(RenderSettings& settings) {
    ImGui::Text("Tracer Configuration");
    ImGui::Checkbox("Enable Tracers", &settings.enableTracers);
    ImGui::Separator();
    const char* origins[] = { "Bottom Center", "Crosshair", "Top Screen" };
    ImGui::Combo("Origin Point", &settings.tracerOrigin, origins, 3);
    ImGui::SliderFloat("Line Thickness", &settings.tracerThickness, 0.5f, 5.0f);
    ImGui::ColorEdit3("Tracer Color", settings.tracerColor);
}

void UIManager::RenderRadarConfig(RenderSettings& settings) {
    ImGui::Text("2D Radar Configuration");
    ImGui::Checkbox("Enable Radar Widget", &settings.enableRadar);
    ImGui::Separator();
    ImGui::SliderFloat("Radar Zoom", &settings.radarZoom, 0.5f, 3.0f);
}

void UIManager::RenderChamsConfig(RenderSettings& settings) {
    ImGui::Text("Chams & Material Override");
    ImGui::Checkbox("Enable Chams Simulation", &settings.enableChams);
    ImGui::Separator();
    const char* modes[] = { "Flat Shaded", "Textured Fullbright", "Wireframe" };
    ImGui::Combo("Material Mode", &settings.chamsMode, modes, 3);
    ImGui::ColorEdit4("Chams Tint Color", settings.chamsColor);
}

void UIManager::RenderSkyConfig(RenderSettings& settings) {
    ImGui::Text("Sky Changer & Environment");
    ImGui::Checkbox("Enable Sky Override", &settings.enableSkyChanger);
    ImGui::Separator();
    ImGui::ColorEdit3("Sky Color Tint", settings.skyColor);
}

void UIManager::RenderWorldConfig(RenderSettings& settings) {
    ImGui::Text("World & Camera Visuals");
    ImGui::SliderFloat("Field of View (FOV)", &settings.fovValue, 60.0f, 140.0f);
    ImGui::ColorEdit3("World Color Grading", settings.worldColor);
}

void UIManager::RenderMiscConfig(RenderSettings& settings) {
    ImGui::Text("Miscellaneous Visuals");
    ImGui::Checkbox("No-Flash Simulation", &settings.noFlash);
    if (settings.noFlash) {
        ImGui::SliderFloat("Flash Alpha Intensity", &settings.flashAlpha, 0.0f, 1.0f);
    }
    ImGui::Checkbox("Smoke Wireframe Mode", &settings.smokeWireframe);
}
