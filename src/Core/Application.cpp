#include "Core/Application.h"
#include "Core/Simulation.h"
#include "Rendering/Renderer.h"
#include "UI/UIManager.h"

#include <GLFW/glfw3.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <cstdio>

Application::Application() : m_Window(nullptr) {}
Application::~Application() {}

bool Application::Init() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    m_Window = glfwCreateWindow(m_Width, m_Height, "NovaResearch // CS2 Visual Research Demo", nullptr, nullptr);
    if (!m_Window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1); // Enable VSync

    return true;
}

void Application::Run() {
    Simulation simulation;
    Renderer renderer;
    UIManager uiManager;
    uiManager.Init(m_Window);

    RenderSettings settings;
    float lastTime = (float)glfwGetTime();

    while (!glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();

        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        simulation.Update(deltaTime);

        int display_w, display_h;
        glfwGetFramebufferSize(m_Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.12f, 0.14f, 0.19f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.RenderSimulationScene(simulation.GetEntities(), settings);
        renderer.RenderRadarOverlay(simulation.GetEntities(), settings);
        uiManager.Render(settings, simulation);

        glfwSwapBuffers(m_Window);
    }

    uiManager.Shutdown();
}

void Application::Shutdown() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();
}
