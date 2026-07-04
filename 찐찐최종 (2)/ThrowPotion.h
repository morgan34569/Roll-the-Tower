#ifndef THROWPOTION_H
#define THROWPOTION_H
#include "Item.h"
#include "Attribute.h"

class ThrowPotion : public Item {
private:
    int damage, burn, vulnerable, damaged;
    Element element;
public:
    ThrowPotion(int code, std::string name, int price, int dmg = 0, int brn = 0, int vuln = 0, int dmgd = 0, Element elem = Element::NONE)
        : Item(code, name, price), damage(dmg), burn(brn), vulnerable(vuln), damaged(dmgd), element(elem) {
    }
    void Use(Player& player, Monster& monster) override;
    Item* clone() const override;
};
#endif
