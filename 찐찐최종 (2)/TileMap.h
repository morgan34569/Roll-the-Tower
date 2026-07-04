#ifndef TILEMAP_H
#define TILEMAP_H
#include <vector>
#include <string>
#include "Shop.h"
#include "Player.h"
class Biome;
class GameManager;

class TileMap {
public:
    static const int SIZE = 16;

private:
    char map[SIZE][SIZE];
    int playerX, playerY;
    int gold;
    Shop shop;
    Biome* currentBiome;

    int currentBiomeIndex;

    // 보스를 몇 번 클리어했는지 기록
    int bossClearCount;

    // 이미 클리어한 맵 번호 목록
    std::vector<int> clearedBiomeIndexes;

    // 새 맵 생성 공통 처리
    void setupNewMap();

    // 지형별 타일 변환 적용
    void applyBiomeTileOverrides();

    // 다음 맵 선택지 생성
    std::vector<int> makeNextBiomeChoiceIndexes() const;

public:
    TileMap();
    TileMap(bool loadMode);   // ← 추가
    ~TileMap();

    Biome* getBiome() const { return currentBiome; }
    char getTile(int x, int y) const { return map[y][x]; }
    int getBiomeIndex() const;
    int getSize() { return SIZE; }
    void setPlayerPos(int x, int y) { playerX = x; playerY = y; }
    void loadBiome(int index);
    void loadMapString(const std::string& s);
    void initMap();
    void generateMap();
    std::vector<std::string> getMapLines() const;
    bool movePlayerOneStep(int dx, int dy);
    char getCurrentTile() const;
    void clearCurrentTile();
    int getPlayerX() const;
    int getPlayerY() const;
    int getGold() const;
    const char* getTileName(char tile) const;
    void openShop(Player& player);
    void openEvent(Player& player, Biome& biome, GameManager& gm);
    void monsterReward(Player& player);
    void bossReward(Player& player);
    void startNextMap();
};
#endif