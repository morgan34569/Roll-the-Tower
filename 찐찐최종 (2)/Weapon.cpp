#include "Weapon.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

using namespace std;

Weapon::Weapon(int code, std::string name, int price, int attackBonus, Element elem,
    Skill* firstSkill, Skill* secondSkill)
    : Item(code, name, price), attackBonus(attackBonus), element(elem),
    firstSkill(firstSkill), secondSkill(secondSkill) {
    if (this->firstSkill == nullptr) {
        this->firstSkill = new StrikeSkill();
    }

    if (this->secondSkill == nullptr) {
        this->secondSkill = new PowerStrikeSkill();
    }
}

Weapon::Weapon(const Weapon& other)
    : Item(other.code, other.name, other.price), attackBonus(other.attackBonus), element(other.element),
    firstSkill(other.firstSkill->clone()), secondSkill(other.secondSkill->clone()) {
}
Weapon::~Weapon() {
    delete firstSkill;
    delete secondSkill;
}

std::string Weapon::getBattleActionText(int actionNumber) const {
    if (actionNumber == 1) {
        return firstSkill->getDescription();
    }

    return secondSkill->getDescription();
}

void Weapon::printExtraBattleStatus(Player& player) const {
    firstSkill->printExtraPlayerStatus(player);
    secondSkill->printExtraPlayerStatus(player);
}

void Weapon::useBattleAction(Player& player, Monster& monster, int actionNumber) {
    if (actionNumber == 1) {
        firstSkill->use(player, monster, element);
    }
    else {
        secondSkill->use(player, monster, element);
    }
}

void Weapon::Use(Player& player, Monster& monster) {
    cout << "\n[" << getName() << "]을(를) 장착했습니다!\n";

    player.equipWeapon(this);

    if (attackBonus > 0) {
        cout << "추가 공격력 +" << attackBonus << "\n";
    }
}

Item* Weapon::clone() const {
    return new Weapon(*this);
}
