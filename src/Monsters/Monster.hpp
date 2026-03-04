#pragma once

#include "../Entity.hpp"

class Monster : public Entity
{
public:
    bool dead = false;
    int health = 10;
    int strength = 0;

    void Start(Vec2 _pos) override
    {
        m_character = 'M';
        m_position = _pos;
        dice.push_back((Die){.sides = 10});
    }

    void Update() override
    {
        //nothing
    }
};