#ifndef BIOMES_H
#define BIOMES_H

#include <string>
#include <iostream>
#include <cstdlib>
#include "Attribute.h"
#include "Monster.h"
#include "Player.h"

// ==========================================
// 부모 클래스 (Biome)
// ==========================================
class Biome {
public:
    virtual ~Biome() {}
    virtual std::string getName() const = 0;

    virtual int modifyDiceRoll(int& dice) { return dice; }
    virtual int modifyDamage(int damage, Element attackElem) { return damage; }

    // 일반 몬스터 생성
    virtual Monster* spawnMonster() = 0;

    // 보스 몬스터 생성
    // 따로 지정하지 않은 바이옴은 기본 보스로 장수말벌 사용
    virtual Monster* spawnBossMonster() {
        return new GiantHornet();
    }

    virtual void onTurnEnd(Player& player, Monster* monster) {}
    virtual bool isAttackMissed() { return false; }
    virtual void onStep(Player& player) {}
    virtual void onDiceRoll(Player& player) {}

    virtual char getTileOverride(char originalTile) { return originalTile; }
    virtual float getGoldMultiplier() { return 1.0f; }
};

// ==========================================
// 공통 몬스터 스폰 함수
// ==========================================

// 평원 몬스터 묶음
static Monster* spawnPlainMonster() {
    int type = rand() % 5;

    if (type == 0) {
        return new JawWorm();
    }
    else if (type == 1) {
        return new BallBug();
    }
    else if (type == 2) {
        return new SporeFungus();
    }
    else if (type == 3) {
        return new Mosquito();
    }
    else {
        return new InfectedHost();
    }
}

// 설원 몬스터 묶음
static Monster* spawnSnowMonster() {
    int type = rand() % 5;

    if (type == 0) {
        return new Snowman();
    }
    else if (type == 1) {
        return new SeaAnemone();
    }
    else if (type == 2) {
        return new Yeti();
    }
    else if (type == 3) {
        return new WolfSpirit();
    }
    else {
        return new EarthTurtle();
    }
}

// 화산 몬스터 묶음
static Monster* spawnVolcanoMonster() {
    int type = rand() % 5;

    if (type == 0) {
        return new LavaSlime();
    }
    else if (type == 1) {
        return new FireBat();
    }
    else if (type == 2) {
        return new FireImp();
    }
    else if (type == 3) {
        return new Demon();
    }
    else {
        return new SoulSword();
    }
}

// 고대의 무기고 몬스터 묶음
// 평원 + 설원 + 화산 몬스터 중 랜덤 등장
// 단, 속성은 전부 NONE으로 변경
static Monster* spawnAllMonsterAsNoneElement() {
    Monster* monster = nullptr;

    int group = rand() % 3;

    if (group == 0) {
        monster = spawnPlainMonster();
    }
    else if (group == 1) {
        monster = spawnSnowMonster();
    }
    else {
        monster = spawnVolcanoMonster();
    }

    monster->setElement(Element::NONE);
    return monster;
}

// ==========================================
// 1. 평원
// 평원 몬스터 등장
// ==========================================
class NormalBiome : public Biome {
public:
    std::string getName() const override {
        return "평원";
    }

    Monster* spawnMonster() override {
        return spawnPlainMonster();
    }

    Monster* spawnBossMonster() override {
        return new GiantHornet();
    }
};

// ==========================================
// 2. 설원
// 설원 몬스터 등장
// 보스: 정령
// ==========================================
class Snowfield : public Biome {
public:
    std::string getName() const override {
        return "설원";
    }

    int modifyDiceRoll(int& dice) override {
        if (dice == 1) {
            std::cout << "\n[설원] 주사위가 1이 나왔지만, 생존 본능으로 2로 보정됩니다!\n";
            dice = 2;
        }

        std::cout << "\n[설원 효과] 거센 눈보라로 인해 발이 푹푹 빠집니다! (이동력 -1)\n";

        int finalMove = dice - 1;

        if (finalMove < 1) {
            return 1;
        }

        return finalMove;
    }

    Monster* spawnMonster() override {
        return spawnSnowMonster();
    }

    Monster* spawnBossMonster() override {
        return new ElementalBoss();
    }
};

// ==========================================
// 3. 화산
// 화산 몬스터 등장
// 보스: 흑요석 골렘
// ==========================================
class Volcano : public Biome {
public:
    std::string getName() const override {
        return "화산";
    }

    int modifyDamage(int damage, Element attackElem) override {
        if (attackElem == Element::FIRE) {
            std::cout << "[화산 효과] 뜨거운 열기가 불 속성 공격을 폭발적으로 증폭시킵니다! (피해량 +30%)\n";
            return static_cast<int>(damage * 1.3);
        }
        else if (attackElem == Element::WATER) {
            std::cout << "[화산 효과] 펄펄 끓는 열기로 인해 물 속성 공격이 증발해버립니다... (피해량 -30%)\n";
            return static_cast<int>(damage * 0.7);
        }

        return damage;
    }

    Monster* spawnMonster() override {
        return spawnVolcanoMonster();
    }

    Monster* spawnBossMonster() override {
        return new ObsidianGolem();
    }
};

// ==========================================
// 4. 바다
// 설원 몬스터 등장
// 보스: 정령
// ==========================================
class Ocean : public Biome {
public:
    std::string getName() const override {
        return "바다";
    }

    int modifyDamage(int damage, Element attackElem) override {
        if (attackElem == Element::WATER) {
            std::cout << "[바다 효과] 풍부한 수분이 물 속성 공격을 강화합니다! (피해량 +30%)\n";
            return static_cast<int>(damage * 1.3);
        }
        else if (attackElem == Element::FIRE) {
            std::cout << "[바다 효과] 습한 환경 탓에 불꽃의 위력이 약해집니다... (피해량 -30%)\n";
            return static_cast<int>(damage * 0.7);
        }

        return damage;
    }

    Monster* spawnMonster() override {
        return spawnSnowMonster();
    }

    Monster* spawnBossMonster() override {
        return new ElementalBoss();
    }
};

// ==========================================
// 5. 사막
// 화산 몬스터 등장
// 보스: 흑요석 골렘
// ==========================================
class Desert : public Biome {
public:
    std::string getName() const override {
        return "사막";
    }

    int modifyDamage(int damage, Element attackElem) override {
        if (attackElem == Element::NATURE) {
            std::cout << "[사막 효과] 메마른 환경 탓에 자연 공격이 약화됩니다! (피해량 -30%)\n";
            return static_cast<int>(damage * 0.7);
        }

        return damage;
    }

    bool isAttackMissed() override {
        if (rand() % 100 < 10) {
            std::cout << "\n[사막 효과] 앗! 짙은 모래바람에 시야가 가려 공격이 빗나갔습니다!\n";
            return true;
        }

        return false;
    }

    Monster* spawnMonster() override {
        return spawnVolcanoMonster();
    }

    Monster* spawnBossMonster() override {
        return new ObsidianGolem();
    }
};

// ==========================================
// 6. 고대의 무기고
// 모든 일반 몬스터 등장
// 단, 속성은 전부 NONE
// 보스: 정령 또는 흑요석 골렘, 속성 NONE
// ==========================================
class AncientArmory : public Biome {
public:
    std::string getName() const override {
        return "고대의 무기고";
    }

    int modifyDamage(int damage, Element attackElem) override {
        if (attackElem == Element::NONE) {
            std::cout << "[고대의 무기고] 주변에 널린 날카로운 무기 파편들이 타격에 힘을 실어줍니다! (물리 피해량 +5)\n";
            return damage + 5;
        }

        return damage;
    }

    Monster* spawnMonster() override {
        return spawnAllMonsterAsNoneElement();
    }

    Monster* spawnBossMonster() override {
        Monster* boss = nullptr;

        int type = rand() % 2;

        if (type == 0) {
            boss = new ElementalBoss();
        }
        else {
            boss = new ObsidianGolem();
        }

        boss->setElement(Element::NONE);
        return boss;
    }
};

// ==========================================
// 7. 벼락 맞은 골짜기
// 평원 몬스터 등장
// 보스: 장수말벌
// ==========================================
class ThunderousPeak : public Biome {
public:
    std::string getName() const override {
        return "벼락 맞은 골짜기";
    }

    void onDiceRoll(Player& player) override {
        if (rand() % 100 < 20) {
            std::cout << "\n[벼락 맞은 골짜기] 우르릉 쾅쾅! 머리 위로 벼락이 떨어졌습니다! (체력 -3)\n";
            player.takeDamage(3);
            system("pause");
        }
    }

    int modifyDamage(int damage, Element attackElem) override {
        std::cout << "[벼락 맞은 골짜기] 무기에 번개의 기운이 깃들어 추가 피해를 입힙니다! (피해량 +3)\n";
        return damage + 3;
    }

    Monster* spawnMonster() override {
        return spawnPlainMonster();
    }

    Monster* spawnBossMonster() override {
        return new GiantHornet();
    }
};

// ==========================================
// 8. 심연
// 심연 전용 몬스터 등장
// ==========================================
class Abyss : public Biome {
public:
    std::string getName() const override {
        return "심연";
    }

    void onStep(Player& player) override {
        std::cout << "\n[심연 효과] 깊은 어둠이 생명력을 갉아먹습니다! (체력 -2)\n";
        player.takeDamage(2);
        system("pause");
    }

    Monster* spawnMonster() override {
        return new AbyssCrawler();
    }

    Monster* spawnBossMonster() override {
        return new AbyssLord();
    }
};

#endif