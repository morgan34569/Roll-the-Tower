#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "TileMap.h"
#include "Player.h"
#include <vector>
#include <string>

class GameManager {
private:
    TileMap map;
    Player player;
    int diceValue;
    int moveCount;
    int diceChance;
    bool isRunning;
    int currentStage;
    bool gameCleared;

public:
    GameManager();
    GameManager(bool loadMode);
    bool isGameCleared() const { return gameCleared; }
    int getmoveCount();
    int setmoveCount(int NUM);
    int getCurrentStage() const { return currentStage; }
    int getMoveCount() const { return moveCount; }
    int getDiceValue() const { return diceValue; }

    Player& getPlayer() { return player; }
    const Player& getPlayer() const { return player; }
    TileMap& getMap() { return map; }
    const TileMap& getMap() const { return map; }

    void setCurrentStage(int v) { currentStage = v; }
    void setMoveCount(int v) { moveCount = v; }
    void setDiceValue(int v) { diceValue = v; }

    void giveMonsterReward(Player& player);
    void start();
    void printGameScreen() const;
    void handleInput(char input);
    void rollDice();
    void movePlayer(char input);
    void handleTileEvent();
    void printDiceImageLines(int value, std::vector<std::string>& lines) const;
};
#endif