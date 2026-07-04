#ifndef ARMOR_H
#define ARMOR_H
#include "Item.h"

class Armor : public Item {
private:
    int defenseReduction;
    int maxHpBonus;
public:
    Armor(int code, std::string name, int price, int def, int hpBonus = 0)
        : Item(code, name, price), defenseReduction(def), maxHpBonus(hpBonus) {
    }
    int getDefenseReduction() const { return defenseReduction; }
    int getMaxHpBonus() const { return maxHpBonus; }
    void Use(Player& player, Monster& monster) override;
    Item* clone() const override;
};
#endif
