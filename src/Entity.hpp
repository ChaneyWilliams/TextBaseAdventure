#pragma once
#include "fogpi/Math.hpp"
#include "Dice.hpp"

class Room;

class Entity {
    public:
        Room* room;

        virtual void Start(Vec2 _pos) {}
        virtual void Update() {}

        Vec2 GetPosition() { return m_position; };
        char Draw() { return m_character; }
        std::vector<Die> dice;

    protected:
        Vec2 m_position;
        char m_character;
};