#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
    void Death();
    void Healing();
private:
    int m_keyCount = 0;
    int m_goldCount = 0;
    int m_health = 100;
};