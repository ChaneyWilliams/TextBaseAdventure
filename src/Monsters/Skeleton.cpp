#include "Skeleton.hpp"

void Skeleton::Start(Vec2 _pos)
{
    m_character = 'B';
    m_position = _pos;
    strength = 3;
    dice.push_back((Die){.sides = 6});
}

void Skeleton::Update()
{

    Vec2 tryPos = m_position + direction;
    if (room->GetLocation(tryPos) == ' ' || room->GetLocation(tryPos) == 'P')
    {
        m_position = tryPos;
        if (room->GetLocation(tryPos) == 'P')
        {
            room->Combat(tryPos);
        }
    }
    else
    {
        direction *= -1.0f;
        tryPos = m_position + direction;
        m_position = m_position + direction;
        if (room->GetLocation(tryPos) == 'P')
        {
            room->Combat(tryPos);
        }
    }
}