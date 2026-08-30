#ifndef BIOMES_H
#define BIOMES_H

#include <string>
#include <iostream>
#include <cstdlib>
#include "Attribute.h"
#include "Monster.h"
#include "Player.h" 

// ==========================================
// 0. 부모 클래스 (Biome)
// ==========================================
class Biome {
public:
    virtual ~Biome() {}
    virtual std::string getName() const = 0;

    virtual int modifyDiceRoll(int& dice) { return dice; }
    virtual int modifyDamage(int damage, Element attackElem) { return damage; }

    // 일반 몬스터 생성
    virtual Monster* spawnMonster() = 0;

    // 보스 몬스터 생성 (기본값: 장수말벌)
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
// 1. 평원 (턱벌레, 공벌레)
// ==========================================
class NormalBiome : public Biome {
public:
    std::string getName() const override { return "평원"; }
    Monster* spawnMonster() override {
        return (rand() % 2 == 0) ? static_cast<Monster*>(new JawWorm()) : static_cast<Monster*>(new BallBug());
    }
    Monster* spawnBossMonster() override { return new GiantHornet(); }
};

// ==========================================
// 2. 설원 (스노우맨, 예티)
// ==========================================
class Snowfield : public Biome {
public:
    std::string getName() const override { return "설원"; }

    int modifyDiceRoll(int& dice) override {
        if (dice == 1) {
            std::cout << "\n[설원] 주사위가 1이 나왔지만, 생존 본능으로 2로 보정됩니다!\n";
            dice = 2;
        }
        std::cout << "\n[설원 효과] 거센 눈보라로 인해 발이 푹푹 빠집니다! (이동력 -1)\n";
        int finalMove = dice - 1;
        return (finalMove < 1) ? 1 : finalMove;
    }

    Monster* spawnMonster() override {
        return (rand() % 2 == 0) ? static_cast<Monster*>(new Snowman()) : static_cast<Monster*>(new Yeti());
    }
    Monster* spawnBossMonster() override { return new ElementalBoss(); }
};

// ==========================================
// 3. 화산 (용암 슬라임, 화염 임프)
// ==========================================
class Volcano : public Biome {
public:
    std::string getName() const override { return "화산"; }

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
        return (rand() % 2 == 0) ? static_cast<Monster*>(new LavaSlime()) : static_cast<Monster*>(new FireImp());
    }
    Monster* spawnBossMonster() override { return new ObsidianGolem(); }
};

// ==========================================
// 4. 재의 숲 (화염 박쥐, 화염 임프)
// ==========================================
class AshForest : public Biome {
public:
    std::string getName() const override { return "재의 숲"; }

    int modifyDamage(int damage, Element attackElem) override {
        if (attackElem == Element::FIRE) {
            std::cout << "[재의 숲] 공기 중의 불씨가 불 속성 공격을 돕습니다! (피해량 +15%)\n";
            return static_cast<int>(damage * 1.15);
        }
        return damage;
    }

    Monster* spawnMonster() override {
        return (rand() % 2 == 0) ? static_cast<Monster*>(new FireBat()) : static_cast<Monster*>(new FireImp());
    }
    Monster* spawnBossMonster() override { return new ObsidianGolem(); }
};

// ==========================================
// 5. 바다 (말미잘, 대지거북)
// ==========================================
class Ocean : public Biome {
public:
    std::string getName() const override { return "바다"; }

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
        return (rand() % 2 == 0) ? static_cast<Monster*>(new SeaAnemone()) : static_cast<Monster*>(new EarthTurtle());
    }
    Monster* spawnBossMonster() override { return new ElementalBoss(); }
};

// ==========================================
// 6. 사막 (공벌레)
// ==========================================
class Desert : public Biome {
public:
    std::string getName() const override { return "사막"; }

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

    Monster* spawnMonster() override { return new BallBug(); }
    Monster* spawnBossMonster() override { return new ObsidianGolem(); }
};

// ==========================================
// 7. 울창한 숲 (버섯포자, 턱벌레)
// ==========================================
class Forest : public Biome {
public:
    std::string getName() const override { return "울창한 숲"; }

    void onTurnEnd(Player& player, Monster* monster) override {
        std::cout << "[울창한 숲] 숲의 따뜻한 생명력이 퍼져나갑니다! (나와 적 체력 5 회복)\n";
        player.heal(5);
        monster->heal(5);
    }

    Monster* spawnMonster() override {
        return (rand() % 2 == 0) ? static_cast<Monster*>(new SporeFungus()) : static_cast<Monster*>(new JawWorm());
    }
    Monster* spawnBossMonster() override { return new GiantHornet(); }
};

// ==========================================
// 8. 부패한 늪 (모기, 감염체)
// ==========================================
class PoisonSwamp : public Biome {
public:
    std::string getName() const override { return "부패한 늪"; }

    void onTurnEnd(Player& player, Monster* monster) override {
        std::cout << "[부패한 늪] 치명적인 독기가 스며듭니다! (플레이어 피해 3)\n";
        player.takeDamage(3);
    }

    Monster* spawnMonster() override {
        return (rand() % 2 == 0) ? static_cast<Monster*>(new Mosquito()) : static_cast<Monster*>(new InfectedHost());
    }
    Monster* spawnBossMonster() override { return new GiantHornet(); }
};

// ==========================================
// 9. 심연 (악마)
// ==========================================
class Abyss : public Biome {
public:
    std::string getName() const override { return "심연"; }

    void onStep(Player& player) override {
        std::cout << "\n[심연 효과] 깊은 어둠이 생명력을 갉아먹습니다! (체력 -2)\n";
        player.takeDamage(2);
        system("pause");
    }

    Monster* spawnMonster() override { return new Demon(); }
    Monster* spawnBossMonster() override { return new AbyssLord(); }
};

// ==========================================
// 10. 성역 (영혼이 깃든 검)
// ==========================================
class Sanctuary : public Biome {
public:
    std::string getName() const override { return "성역"; }

    void onStep(Player& player) override {
        std::cout << "\n[성역 효과] 따스한 빛이 상처를 치유합니다! (체력 +2)\n";
        player.heal(2);
        system("pause");
    }

    Monster* spawnMonster() override { return new SoulSword(); }
    Monster* spawnBossMonster() override { return new ElementalBoss(); }
};

// ==========================================
// 11. 벼락 맞은 골짜기 (늑대영혼)
// ==========================================
class ThunderousPeak : public Biome {
public:
    std::string getName() const override { return "벼락 맞은 골짜기"; }

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

    Monster* spawnMonster() override { return new WolfSpirit(); }
    Monster* spawnBossMonster() override { return new ElementalBoss(); }
};

// ==========================================
// 12. 피의 투기장 (악마, 영혼이 깃든 검)
// ==========================================
class BloodArena : public Biome {
public:
    std::string getName() const override { return "피의 투기장"; }
    float getGoldMultiplier() override { return 2.0f; }

    char getTileOverride(char originalTile) override {
        if (originalTile == '.' || originalTile == 'S' || originalTile == 'E') {
            return 'M';
        }
        return originalTile;
    }

    Monster* spawnMonster() override {
        return (rand() % 2 == 0) ? static_cast<Monster*>(new Demon()) : static_cast<Monster*>(new SoulSword());
    }
    Monster* spawnBossMonster() override { return new ObsidianGolem(); }
};

// ==========================================
// 13. ???의 방 (감염체, 악마)
// ==========================================
class MysteryRoom : public Biome {
public:
    std::string getName() const override { return "???의 방"; }

    char getTileOverride(char originalTile) override {
        if (originalTile == 'B') return 'B';
        return 'E';
    }

    Monster* spawnMonster() override {
        return (rand() % 2 == 0) ? static_cast<Monster*>(new InfectedHost()) : static_cast<Monster*>(new Demon());
    }
    Monster* spawnBossMonster() override { return new AbyssLord(); }
};

// ==========================================
// 14. 저주받은 묘지 (늑대영혼, 감염체)
// ==========================================
class CursedGraveyard : public Biome {
public:
    std::string getName() const override { return "저주받은 묘지"; }

    void onTurnEnd(Player& player, Monster* monster) override {
        std::cout << "\n[저주받은 묘지] 망자의 기운이 생명력을 빨아들입니다! (내 체력 -2, 적 체력 +2)\n";
        player.takeDamage(2);
        monster->heal(2);
    }

    Monster* spawnMonster() override {
        return (rand() % 2 == 0) ? static_cast<Monster*>(new WolfSpirit()) : static_cast<Monster*>(new InfectedHost());
    }
    Monster* spawnBossMonster() override { return new AbyssLord(); }
};

// ==========================================
// 15. 고대의 무기고 (영혼이 깃든 검)
// ==========================================
class AncientArmory : public Biome {
public:
    std::string getName() const override { return "고대의 무기고"; }

    int modifyDamage(int damage, Element attackElem) override {
        if (attackElem == Element::NONE) {
            std::cout << "[고대의 무기고] 주변에 널린 날카로운 무기 파편들이 타격에 힘을 실어줍니다! (물리 피해량 +5)\n";
            return damage + 5;
        }
        return damage;
    }

    Monster* spawnMonster() override {
        Monster* monster = new SoulSword();
        monster->setElement(Element::NONE);
        return monster;
    }
    Monster* spawnBossMonster() override {
        Monster* boss = new ObsidianGolem();
        boss->setElement(Element::NONE);
        return boss;
    }
};

// ==========================================
// 16. 영원의 빙하 (예티)
// ==========================================
class EternalGlacier : public Biome {
public:
    std::string getName() const override { return "영원의 빙하"; }

    int modifyDiceRoll(int& dice) override {
        std::cout << "\n[영원의 빙하] 뼛속까지 얼어붙는 추위에 몸이 굳어갑니다... (이동력 3 고정)\n";
        return 3;
    }

    Monster* spawnMonster() override { return new Yeti(); }
    Monster* spawnBossMonster() override { return new ElementalBoss(); }
};

#endif