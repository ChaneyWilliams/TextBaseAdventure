#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
    void Death();
    void Healing();
    void Level();
    int health = 10;
    int gold = 0;
    int strength = 1;
    int level = 1;
private:
    int m_keyCount = 0;
};