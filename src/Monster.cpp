#pragma once
#include "Monster.hpp"

void Monster::Start(Vec2 _pos){
    m_character = 'M';
    m_position = _pos;
    dice.push_back((Die){.sides = 10});
}