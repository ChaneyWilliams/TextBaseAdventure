#pragma once
#include "Monster.hpp"
#include "../Room.hpp"
class Goblin : public Monster
{
public:
    Vec2 direction = {1.0f, 0.0f};
    void Start(Vec2 _pos) override;
    void Update() override;
};