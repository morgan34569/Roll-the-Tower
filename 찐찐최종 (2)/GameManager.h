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

public:
    GameManager();
    GameManager(bool loadMode);
    int getmoveCount();
    int setmoveCount(int NUM);
    int getCurrentStage() const { return currentStage; }
    int getMoveCount() const { return moveCount; }       // 추가
    int getDiceValue() const { return diceValue; }

    Player& getPlayer() { return player; }               // 추가
    const Player& getPlayer() const { return player; }   // 추가
    TileMap& getMap() { return map; }                    // 추가
    const TileMap& getMap() const { return map; }        // 추가

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