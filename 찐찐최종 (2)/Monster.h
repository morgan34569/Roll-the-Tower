#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <cmath>
#include "Attribute.h"

class Player;

enum MonsterIntent {
    INTENT_ATTACK,
    INTENT_BLOCK,
    INTENT_BUFF,
    INTENT_DEBUFF,
    INTENT_POISON_ATTACK,
    INTENT_DOUBLE_POISON,
    INTENT_FLIGHT,
    INTENT_BLOOD_BUFF,
    INTENT_PARASITE,
    INTENT_PREPARE,
    INTENT_EXPLODE,

    INTENT_FREEZE,
    INTENT_MELT,
    INTENT_SOLIDIFY,
    INTENT_STEAL_GOLD,
    INTENT_ESCAPE,
    INTENT_ARMOR
};

class Monster {
protected:
    std::string name;
    int hp, maxHP, block, strength, vulnerable, burn, damaged;
    MonsterIntent intent;
    Element element;

public:
    Monster(std::string name, int hp, Element elem = Element::NONE)
        : name(name), hp(hp), maxHP(hp), block(0), strength(0),
        vulnerable(0), burn(0), damaged(0), intent(INTENT_ATTACK), element(elem) {
    }

    virtual ~Monster() {}

    std::string getName() const { return name; }
    int getHP() const { return hp; }
    int getBlock() const { return block; }
    int getStrength() const { return strength; }
    int getVulnerable() const { return vulnerable; }
    int getBurn() const { return burn; }
    int getDamaged() const { return damaged; }
    bool isDead() const { return hp <= 0; }
    Element getElement() const { return element; }

    virtual void onPlayerActionEnd(Player& player) {}

    virtual bool hasEscaped() const {
        return false;
    }

    void setElement(Element elem) {
        element = elem;
    }

    virtual void onBeforePlayerTurn(Player& player) {}

    // [1번에서 추가] 스테이지 스케일링
    virtual void applyStageScaling(int stage) {
        if (stage <= 1) return;

        double multiplier = std::pow(1.2, stage - 1);

        maxHP = static_cast<int>(maxHP * multiplier);
        hp = maxHP;

        strength += (stage - 1) * 2;
    }

    virtual void takeDamage(int damage);
    virtual void addBlock(int amount);
    virtual void addVulnerable(int turn);
    virtual void addBurn(int amount);
    virtual void addDamaged(int amount);
    void applyBurnDamage();
    virtual void clearBlock();

    virtual void heal(int amount) {
        hp += amount;
        if (hp > maxHP) hp = maxHP;
    }

    virtual void decideIntent() = 0;
    virtual void showIntent() const = 0;
    virtual void executeIntent(Player& player) = 0;
    virtual void printExtraStatus() const {}

    virtual void onTurnStart() {
        block = 0;
        if (vulnerable > 0) vulnerable--;
        if (damaged > 0) damaged--;
    }

    virtual void onDeath(Player& player) {}
    virtual Monster* getNextMonsterOnDeath() { return nullptr; }
};

class JawWorm : public Monster {
private:
    int patternIndex;

public:
    JawWorm();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class BallBug : public Monster {
private:
    bool curlUsed;
    int patternIndex;

public:
    BallBug();
    void takeDamage(int damage) override;
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class SporeFungus : public Monster {
private:
    int growth;
    int patternIndex;

public:
    SporeFungus();
    void onTurnStart() override;
    void decideIntent() override;
    void showIntent() const override;
    void printExtraStatus() const override;
    void executeIntent(Player& player) override;
    void onDeath(Player& player) override;
};

class Mosquito : public Monster {
private:
    int patternIndex;
    int blood;
    bool flyingGuard;

public:
    Mosquito();
    void takeDamage(int damage) override;
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class Parasite : public Monster {
private:
    int patternIndex;

public:
    Parasite();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class InfectedHost : public Monster {
private:
    int patternIndex;

public:
    InfectedHost();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
    Monster* getNextMonsterOnDeath() override;
};

class GiantHornet : public Monster {
private:
    int patternIndex;
    bool flyingGuard;

public:
    GiantHornet();
    void takeDamage(int damage) override;
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class IceBear : public Monster {
public:
    IceBear();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class FireBat : public Monster {
private:
    int patternIndex;
    bool halfDamageNextTurn;

public:
    FireBat();
    void takeDamage(int damage) override;
    void onTurnStart() override;
    void decideIntent() override;
    void showIntent() const override;
    void printExtraStatus() const override;
    void executeIntent(Player& player) override;
};

class LavaSlime : public Monster {
private:
    int patternIndex;
    int damageTakenPercent;
    bool melted;

public:
    LavaSlime();
    void takeDamage(int damage) override;
    void decideIntent() override;
    void showIntent() const override;
    void printExtraStatus() const override;
    void executeIntent(Player& player) override;
};

class FireImp : public Monster {
private:
    int patternIndex;

public:
    FireImp();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class Demon : public Monster {
private:
    int patternIndex;
    int stolenGold;
    bool escaped;

public:
    Demon();
    bool hasEscaped() const override;
    void decideIntent() override;
    void showIntent() const override;
    void printExtraStatus() const override;
    void executeIntent(Player& player) override;
};

class SoulSword : public Monster {
private:
    int patternIndex;
    bool finalMode;

public:
    SoulSword();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class ObsidianGolem : public Monster {
private:
    int patternIndex;
    int armor;

public:
    ObsidianGolem();
    void takeDamage(int damage) override;
    void decideIntent() override;
    void showIntent() const override;
    void printExtraStatus() const override;
    void executeIntent(Player& player) override;
};

class Snowman : public Monster {
private:
    int patternIndex;
    bool freezeApplied;

public:
    Snowman();
    void clearBlock() override;
    void onPlayerActionEnd(Player& player) override;
    void decideIntent() override;
    void showIntent() const override;
    void printExtraStatus() const override;
    void executeIntent(Player& player) override;
};

class SeaAnemone : public Monster {
private:
    int patternIndex;

public:
    SeaAnemone();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class Yeti : public Monster {
private:
    int patternIndex;

public:
    Yeti();
    void takeDamage(int damage) override;
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class WolfSpirit : public Monster {
private:
    int patternIndex;
    int etherealCount;

public:
    WolfSpirit();
    void takeDamage(int damage) override;
    void onTurnStart() override;
    void decideIntent() override;
    void showIntent() const override;
    void printExtraStatus() const override;
    void executeIntent(Player& player) override;
};

class EarthTurtle : public Monster {
private:
    int patternIndex;

public:
    EarthTurtle();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class ElementalBoss : public Monster {
private:
    int patternIndex;
    bool icePassive;
    bool waterPassive;

public:
    ElementalBoss();
    void takeDamage(int damage) override;
    void decideIntent() override;
    void showIntent() const override;
    void printExtraStatus() const override;
    void executeIntent(Player& player) override;
};

class AshWolf : public Monster {
public:
    AshWolf();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class SeaSerpent : public Monster {
public:
    SeaSerpent();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class GiantScorpion : public Monster {
public:
    GiantScorpion();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class GiantMantis : public Monster {
public:
    GiantMantis();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class VenomSpider : public Monster {
public:
    VenomSpider();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class AbyssCrawler : public Monster {
public:
    AbyssCrawler();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class AbyssLord : public Monster {
private:
    int patternIndex;
    bool shadowMerged;

public:
    AbyssLord();
    void takeDamage(int damage) override;
    void onTurnStart() override;
    void onBeforePlayerTurn(Player& player) override;
    void decideIntent() override;
    void showIntent() const override;
    void printExtraStatus() const override;
    void executeIntent(Player& player) override;
};

class SanctuaryGuardian : public Monster {
public:
    SanctuaryGuardian();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class StormFalcon : public Monster {
public:
    StormFalcon();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class ObsidianGladiator : public Monster {
public:
    ObsidianGladiator();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class UnknownEntity : public Monster {
public:
    UnknownEntity();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class CursedSkeleton : public Monster {
public:
    CursedSkeleton();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class ArmorySentinel : public Monster {
public:
    ArmorySentinel();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

class GlacierGolem : public Monster {
public:
    GlacierGolem();
    void decideIntent() override;
    void showIntent() const override;
    void executeIntent(Player& player) override;
};

#endif