#include "Core/Application.h"
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Starting NovaResearch CS2 Architectural Demo..." << std::endl;

    Application app;
    if (!app.Init()) {
        std::cerr << "Application initialization failed!" << std::endl;
        return -1;
    }

    app.Run();
    app.Shutdown();

    std::cout << "NovaResearch terminated successfully." << std::endl;
    return 0;
}
