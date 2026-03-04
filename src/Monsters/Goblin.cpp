#include "Goblin.hpp"

void Goblin::Start(Vec2 _pos)
{
    m_character = 'G';
    m_position = _pos;
    strength = 2;
    dice.push_back((Die){.sides = 10});
}

void Goblin::Update()
{

    Vec2 tryPos = m_position + direction;
    char tile = room->GetLocation(tryPos);

    if (tile != '#' && tile != 'D' && tile != 'L')
    {
        m_position = tryPos;
        if (tile == 'P')
        {
            room->Combat(tryPos);
        }
    }
    else
    {
        direction *= -1.0f;
        m_position = m_position + direction;
    }
}
