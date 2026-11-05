#pragma once

struct GLFWwindow;

class Application {
public:
    Application();
    ~Application();

    bool Init();
    void Run();
    void Shutdown();

private:
    GLFWwindow* m_Window;
    int m_Width = 1480;
    int m_Height = 900;
};
