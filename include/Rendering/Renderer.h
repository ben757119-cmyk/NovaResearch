#pragma once
#include <vector>
#include "Core/Simulation.h"

struct RenderSettings {
    bool enableESP = true;
    bool box2D = true;
    bool skeleton = true;
    bool healthBars = true;
    bool names = true;
    bool distance = true;
    bool weapons = true;
    float boxColor[3] = { 0.0f, 0.85f, 1.0f };
    float enemyColor[3] = { 1.0f, 0.2f, 0.2f };
    float teamColor[3] = { 0.2f, 1.0f, 0.3f };

    bool enableTracers = false;
    int tracerOrigin = 0; // 0: Bottom Center, 1: Crosshair, 2: Top
    float tracerColor[3] = { 1.0f, 1.0f, 1.0f };
    float tracerThickness = 1.5f;

    bool enableRadar = true;
    float radarPosX = 50.0f;
    float radarPosY = 50.0f;
    float radarSize = 180.0f;
    float radarZoom = 1.0f;

    bool enableChams = false;
    int chamsMode = 0; // 0: Flat, 1: Textured, 2: Wireframe
    float chamsColor[4] = { 0.8f, 0.4f, 1.0f, 1.0f };

    bool enableSkyChanger = false;
    float skyColor[3] = { 0.12f, 0.15f, 0.25f };
    float worldColor[3] = { 1.0f, 1.0f, 1.0f };
    float fovValue = 90.0f;
    bool noFlash = false;
    float flashAlpha = 0.0f;
    bool smokeWireframe = false;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void RenderSimulationScene(const std::vector<SimulatedEntity>& entities, const RenderSettings& settings);
    void RenderRadarOverlay(const std::vector<SimulatedEntity>& entities, const RenderSettings& settings);
    void RenderESPDrawings(const std::vector<SimulatedEntity>& entities, const RenderSettings& settings);
};
