#ifndef POTION_H
#define POTION_H
#include "Item.h"

class Potion : public Item {
private:
    int healAmount, cureVulnerable, cureWeak, addStrength, addBlock;
public:
    Potion(int code, std::string name, int price, int heal = 0, int cv = 0, int cw = 0, int str = 0, int blk = 0, int fs = 0)
        : Item(code, name, price), healAmount(heal), cureVulnerable(cv), cureWeak(cw), addStrength(str), addBlock(blk + fs) {
    }
    void Use(Player& player, Monster& monster) override;
    Item* clone() const override;

    int getHealAmount() const {
        return healAmount;
    }

    int getCureVulnerable() const {
        return cureVulnerable;
    }

    int getCureWeak() const {
        return cureWeak;
    }

    int getAddStrength() const {
        return addStrength;
    }

    int getAddBlock() const {
        return addBlock;
    }

};
#endif
