#include "Core/Simulation.h"
#include <cmath>
#include <cstdlib>

Simulation::Simulation() {
    InitializeEntities();
}

Simulation::~Simulation() {}

void Simulation::InitializeEntities() {
    m_Entities = {
        {1, "Alpha_Operator", -150.0f, 50.0f, 300.0f, 0.0f, 100, false, "AK-47", true},
        {2, "Bravo_Sniper", 200.0f, -80.0f, 450.0f, 45.0f, 85, false, "AWP", true},
        {3, "Charlie_Scout", 50.0f, 250.0f, 280.0f, 90.0f, 40, false, "Scout", false},
        {4, "Delta_Support", -220.0f, -200.0f, 350.0f, 135.0f, 100, true, "M4A1", true},
        {5, "Echo_Leader", 120.0f, 180.0f, 520.0f, 180.0f, 100, true, "Desert Eagle", true}
    };
}

void Simulation::Update(float deltaTime) {
    if (!enableMovement) return;

    static float timeElapsed = 0.0f;
    timeElapsed += deltaTime * simulationSpeed;

    for (size_t i = 0; i < m_Entities.size(); ++i) {
        float radius = 80.0f + (i * 25.0f);
        float speed = 0.8f + (i * 0.2f);
        m_Entities[i].posX = std::cos(timeElapsed * speed + i) * radius;
        m_Entities[i].posY = std::sin(timeElapsed * speed + i) * radius;
        
        if (i == 2) {
            m_Entities[i].isVisible = (std::fmod(timeElapsed, 4.0f) > 2.0f);
        }
    }
}
