#include "Armor.h"
#include "Player.h"
#include <iostream>

void Armor::Use(Player& player, Monster& monster) {
    std::cout << "\n[" << getName() << "]을(를) 장착했습니다!\n";
    player.equipArmor(this);
}

Item* Armor::clone() const {
    return new Armor(*this);
}
