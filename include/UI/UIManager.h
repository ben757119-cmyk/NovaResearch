#pragma once
#include "Rendering/Renderer.h"
#include "Core/Simulation.h"

class UIManager {
public:
    UIManager();
    ~UIManager();

    void Init(GLFWwindow* window);
    void Render(RenderSettings& settings, Simulation& simulation);
    void Shutdown();

private:
    void RenderSidebar(RenderSettings& settings, Simulation& simulation);
    void RenderESPConfig(RenderSettings& settings);
    void RenderTracerConfig(RenderSettings& settings);
    void RenderRadarConfig(RenderSettings& settings);
    void RenderChamsConfig(RenderSettings& settings);
    void RenderSkyConfig(RenderSettings& settings);
    void RenderWorldConfig(RenderSettings& settings);
    void RenderMiscConfig(RenderSettings& settings);

    int m_ActiveTab = 0;
};
