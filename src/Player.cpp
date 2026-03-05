#include "Player.hpp"
#include "Room.hpp"
#include "fogpi/io.hpp"

void Player::Start(Vec2 _pos) {
    m_character = 'P';
    m_position = _pos;
}

void Player::Update() {
    //while(request_char("hit w to continue: ") != 'w') {}

    char directionInput;

    do {
        directionInput = request_char("wasd and Enter to move");
    } while (directionInput != 'w' &&
             directionInput != 'a' &&
             directionInput != 's' &&
             directionInput != 'd');
    
    Vec2 direction(0.0f);

    switch (directionInput)
    {
    case 'w':
        direction = {0.0f, -1.0f};
        break;
    case 'a':
        direction = {-1.0f, 0.0f};
        break;
    case 's':
        direction = {0.0f, 1.0f};
        break;
    case 'd':
        direction = {1.0f, 0.0f};
        break;
    default:
        direction = {0.0f, 1.0f};
        break;
    }

    Vec2 tryPos = m_position + direction;

    if (room->GetLocation(tryPos) == 'K') {
        m_keyCount++;
        room->ClearLocation(tryPos);
    }

    if (room->GetLocation(tryPos) == ' ') {
        m_position = tryPos;
    }

    if (room->GetLocation(tryPos) == 'D') {
        room->OpenDoor(tryPos);
    }

    if (room->GetLocation(tryPos) == 'L'){
        if (m_keyCount > 0)
        {
            m_keyCount--;
            printf("You used a key to open the door! Keys remaining: %d\n", m_keyCount);
            room->OpenDoor(tryPos);
        }
        else
        {
             printf("The door is locked! You need a key.\n");
        }
    }

    
    if (room->GetLocation(tryPos) == 'T')
    {
        
        if (m_keyCount > 0)
        {
            m_keyCount--;
            printf("You used a key to open the chest! Keys remaining: %d\n", m_keyCount);
            room->ClearLocation(tryPos);
            m_goldCount += 100;

        }
        else
        {

            printf("The chest is locked! You need a key.\n");
        }
    }
}

void Player::Death()
{
    if(m_health<=0)
    {
        printf("Your Gold Count Was:  %d\n", m_goldCount);
        exit(1);
    }
}

void Player:: Healing()
{
    m_health += 20;
}

