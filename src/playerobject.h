#include "gameobject.h"

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

class PlayerObject : public GameObject {
public:
    PlayerObject(glm::vec3 pos,
        glm::vec3 rot,
        glm::vec3 scale,
        string modelName,
        dWorldID w,
        dSpaceID s);

    virtual void update() override;
    virtual void draw() override;

    float maxSpeed = 7;
    float maxAccel = 7;

    float maxHealth = 50;
    float curHealth = maxHealth;
    float targetHealth = curHealth;

    float maxHealthLossSpeed{ 50 };

    glm::vec3 targetVelocity{};
};

#endif // PLAYEROBJECT_H
