#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Attribute.h"
#include "Skill.h"

class Weapon : public Item {
private:
    int attackBonus;
    Element element;
    Skill* firstSkill;
    Skill* secondSkill;

public:
    Weapon(int code, std::string name, int price, int attackBonus = 0, Element elem = Element::NONE,
        Skill* firstSkill = nullptr, Skill* secondSkill = nullptr);
    Weapon(const Weapon& other);
    ~Weapon() override;

    Weapon& operator=(const Weapon&) = delete;

    int getAttackBonus() const {
        return attackBonus;
    }

    Element getElement() const {
        return element;
    }

    std::string getBattleActionText(int actionNumber) const;
    void printExtraBattleStatus(Player& player) const;
    void useBattleAction(Player& player, Monster& monster, int actionNumber);

    void Use(Player& player, Monster& monster) override;
    Item* clone() const override;
};

#endif
