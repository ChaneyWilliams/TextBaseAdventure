#include "Dice.hpp"
#include "Room.hpp"

#include "Player.hpp"

#include "Monsters/Goblin.hpp"
#include "Monsters/Skeleton.hpp"

#include <fstream>
#include <string>
RollStats RollDice(std::vector<Die> _dice);

void Room::Load(std::string _path)
{
    m_map.clear();
    m_doors.clear();

    std::ifstream file;
    file.open(_path);

    if (!file.is_open())
    {
        printf("file not found at: %s \n", _path.c_str());
        exit(1);
    }

    std::string word;
    int number;

    while (file >> word)
    {
        if (word == "level")
        {
            if (file >> number)
            {
                printf("open level: %i\n", number);
            }
        }

        if (word == "next_level")
        {
            if (file >> word)
            {
                m_doors.push_back(Door());
                m_doors[m_doors.size() - 1].path = word;
            }
        }

        if (word == "map")
        {
            m_map.push_back(std::vector<char>());
            while (file >> word)
            {
                if (word == "-2")
                {
                    break;
                }

                if (word == "-1")
                {
                    m_map.push_back(std::vector<char>());
                    continue;
                }

                if (word == "0")
                    m_map[m_map.size() - 1].push_back(' ');
                else
                    m_map[m_map.size() - 1].push_back(word[0]);
            }
        }
    }

    int doorCount = 0;
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            if (m_map[y][x] == 'S')
            {
                if (m_player == nullptr)
                    m_player = new Player();

                m_player->Start(Vec2(x, y));
                m_map[y][x] = ' ';
            }
            if (m_map[y][x] == 'M')
            {
                Monster *monster = (rand() % 2 == 0) ? (Monster *)new Skeleton() : (Monster *)new Goblin();
                monster->Start(Vec2(x, y));
                m_monsters.push_back(monster);
                m_map[y][x] = ' ';
            }
            if (m_map[y][x] == 'D' || m_map[y][x] == 'L')
            {
                if (m_doors.size() - 1 >= doorCount)
                {
                    m_doors[doorCount].pos.x = x;
                    m_doors[doorCount].pos.y = y;
                    doorCount++;
                    if (m_monsters.size() > 0)
                    {
                        m_map[y][x] = 'L';
                    }
                }
            }
        }
    }
    TrySpawnChest();
}

void Room::Update()
{
    Draw();
    if (m_player != nullptr)
    {
        m_player->room = this;
        m_player->Update();
        if (m_monsters.size() > 0)
        {
            for (Monster *monster : m_monsters)
            {
                monster->room = this;
                monster->Update();
            }
        }
        else
        {
            for(Door door : m_doors){
                m_map[door.pos.y][door.pos.x] = 'D';
            }
        }
    }

}

void Room::Draw()
{
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            printf("%c ", GetLocation(Vec2(x, y)));
        }
        printf("\n");
    }
}

char Room::GetLocation(Vec2 _pos)
{

    if (_pos.y >= m_map.size())
        return ' ';

    if (_pos.x >= m_map[_pos.y].size())
        return ' ';

    if (m_player != nullptr)
        if (m_player->GetPosition() == _pos)
            return m_player->Draw();
    for (Monster *monster : m_monsters)
    {
        if (monster->GetPosition() == _pos)
        {
            return monster->Draw();
        }
    }
    return m_map[_pos.y][_pos.x];
}

void Room::ClearLocation(Vec2 _pos)
{
    if (_pos.y >= m_map.size())
        return;

    if (_pos.x >= m_map[_pos.y].size())
        return;

    m_map[_pos.y][_pos.x] = ' ';
}

void Room::OpenDoor(Vec2 _pos)
{
    for (int i = 0; i < m_doors.size(); i++)
    {
        if (m_doors[i].pos == _pos)
        {
            printf("door\n");
            std::string path = m_doors[i].path; // copy it first
            Load(path);                         // now safe
            return;                             // stop iterating, doors are gone
        }
    }
}char leave;

void Room::TrySpawnChest()
{
    if (rand() % 100 >= 20)
        return;

    std::vector<Vec2> openTiles;
    Vec2 playerPos = m_player->GetPosition();

    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            if (m_map[y][x] == ' ' && Vec2(x, y) != playerPos)
                openTiles.push_back(Vec2(x, y));
        }
    }

    if (openTiles.size() < 2)
        return;

    int chestIndex = rand() % openTiles.size();
    Vec2 chestPos = openTiles[chestIndex];
    m_map[chestPos.y][chestPos.x] = 'T';
    openTiles.erase(openTiles.begin() + chestIndex);

    int keyIndex = rand() % openTiles.size();
    Vec2 keyPos = openTiles[keyIndex];
    m_map[keyPos.y][keyPos.x] = 'K';
}

void Room::Combat(Vec2 _pos)
{

    Monster *fighter = nullptr;

    for (Monster *monster : m_monsters)
    {
        if (monster->GetPosition() == _pos)
        {
            fighter = monster;
            break;
        }
    }

    if (!fighter)
    {
        printf("No monster found!\n");
        return;
    }
    char leave;
    printf("FIGHT\n");
    while (m_player->health > 0 && fighter->health > 0)
    {
        RollStats playerRoll = RollDice(m_player->dice);
        RollStats monsterRoll = RollDice(fighter->dice);
        printf("Player: %i, Monster %i\n", playerRoll.total + m_player->strength, monsterRoll.total + fighter->strength);

        if (playerRoll.total + m_player->strength >= monsterRoll.total + fighter->strength)
        {
            fighter->health -= 10;
            printf("Monster Lost 10 Health\n");
        }
        else
        {
            m_player->health -= 10;
            printf("Player Lost 10 Health\n");
        }
        do{
            leave = request_char("Press c for next round");
        }while(leave != 'c');
    }
    // just deleting the monster at health = 0
    // the vector complicates things just a little bit because
    // it stores pointers so even if we delete just the monster object
    // the vector will still reference the dead pointer. So just we're
    // just deleting the Monster AND the pointer (plus it catches anything else that should be dead)
    for (int i = m_monsters.size() - 1; i >= 0; --i)
    {
        if (m_monsters[i]->health <= 0)
        {
            delete m_monsters[i];
            m_monsters.erase(m_monsters.begin() + i);
        }
    }
    if(m_player->health <= 0){
        //die funct;
    }
    else{
        m_player->gold += rand() % 11;
        m_player->strength++;
        printf("Player Won!\nLevel Up!\nStrength: %i\n", m_player->strength);
        printf("Player Current Health: %i\nPlayer Got Gold: %i\n", m_player->health, m_player->gold);
        do{
            leave = request_char("Press c to continue");
        }while(leave != 'c');
    }
    
}
