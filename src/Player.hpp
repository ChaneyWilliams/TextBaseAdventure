#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
    int health = 100;
    int strength = 1;
    int gold = 0;
private:
    int m_keyCount = 0;
};