#pragma once

#include "Entity.hpp"

class Monster : public Entity
{
public:
    int health = 10;
    void Start(Vec2 _pos);
};