#pragma once
#include <vector>
#include <string>

struct SimulatedEntity {
    int id;
    std::string name;
    float posX, posY, posZ;
    float rotYaw;
    int health;
    bool isTeamMate;
    std::string activeWeapon;
    bool isVisible;
};

class Simulation {
public:
    Simulation();
    ~Simulation();

    void Update(float deltaTime);
    const std::vector<SimulatedEntity>& GetEntities() const { return m_Entities; }

    bool enableMovement = true;
    float simulationSpeed = 1.0f;

private:
    std::vector<SimulatedEntity> m_Entities;
    void InitializeEntities();
};
