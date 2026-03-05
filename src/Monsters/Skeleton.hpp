#pragma once
#include "Monster.hpp"
#include "../Room.hpp"
class Skeleton : public Monster
{
public:
    Vec2 direction = {0.0f, 1.0f};
    void Start(Vec2 _pos) override;
    void Update() override;
};