#include "Potion.h"
#include "Player.h"
#include <iostream>

void Potion::Use(Player& player, Monster& monster) {
    std::cout << getName() << " 사용!\n";
    if (healAmount > 0) player.heal(healAmount);
    if (cureVulnerable > 0) player.getStatus().removeVulnerable(cureVulnerable);
    if (cureWeak > 0) player.getStatus().removeWeak(cureWeak);
    if (addStrength > 0) player.getStatus().addStrength(addStrength);
    if (addBlock > 0) player.addBlock(addBlock);
}

Item* Potion::clone() const {
    return new Potion(*this);
}
