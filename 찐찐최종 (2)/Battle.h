#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Monster.h"

class Biome; // 지형 클래스 전방 선언

class Battle {
private:
    static bool lastMonsterEscaped;

public:
    // 1. 지형 버프를 받는 전투 시작 함수
    static bool startMonsterBattle(Player& player, Biome* biome, int Stage);
    static bool startBossBattle(Player& player, Biome* biome);

    // 악마 도망 여부 확인용
    static bool didLastMonsterEscape();

    // 2. 인벤토리에서 호출하는 랜덤 몬스터 생성 함수 (딱 한 번만 선언)
    static Monster* createRandomMonster();
};

#endif
