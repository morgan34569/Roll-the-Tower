#ifndef EVENT_H
#define EVENT_H
#include "Player.h"
#include "Biomes.h"

class GameManager;

class Event {
public:
    Event();
    void EventOpen(Player& player, Biome* biome, GameManager& gm);
};
#endif
