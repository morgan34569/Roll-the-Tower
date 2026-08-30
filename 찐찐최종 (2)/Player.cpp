#include "Player.h"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include <iostream>
using namespace std;

Player::Player() : hp(100), maxHP(100), block(0), gold(500), potionCount(3), equippedArmor(nullptr) {
    equippedWeapon = new Weapon{ 1001, "기본검", 0, 0 };
}

void Player::takeDamage(int damage) {
    if (status.getVulnerable() > 0) damage += damage / 2;
    if (equippedArmor != nullptr) damage -= equippedArmor->getDefenseReduction();
    if (damage < 0) damage = 0;

    int actualDamage = (damage > block) ? damage - block : 0;
    block = (damage > block) ? 0 : block - damage;
    hp -= actualDamage;
    cout << "플레이어가 " << actualDamage << " 피해를 받았습니다.\n";
}

void Player::takeDirectDamage(int damage) {
    if (damage < 0) damage = 0;

    hp -= damage;
    if (hp < 0) hp = 0;

    cout << "플레이어가 방어를 무시하고 " << damage << " 피해를 받았습니다.\n";
}

void Player::applyPoisonBeforeAction() {
    int poison = status.getPoison();

    if (poison > 0) {
        cout << "\n[독] 플레이어가 행동하기 전에 독 피해 " << poison << "을 받습니다.\n";
        takeDirectDamage(poison);
        status.decreasePoison();
        cout << "[독] 남은 독 수치: " << status.getPoison() << "\n";
    }

    int parasite = status.getParasite();

    if (parasite > 0) {
        cout << "\n[기생] 플레이어가 행동하기 전에 기생 피해 " << parasite << "을 받습니다.\n";
        takeDirectDamage(parasite);
        cout << "[기생] 현재 기생 수치: " << status.getParasite() << "\n";
    }
}

void Player::applyBurnAfterAction() {
    int burn = status.getBurn();

    if (burn > 0) {
        cout << "\n[화상] 플레이어의 행동이 끝난 뒤 화상 피해 " << burn << "을 받습니다.\n";
        takeDirectDamage(burn);
        status.decreaseBurn();
        cout << "[화상] 남은 화상 수치: " << status.getBurn() << "\n";
    }
}

void Player::heal(int amount) { hp = (hp + amount > maxHP) ? maxHP : hp + amount; }
void Player::addBlock(int amount) { block += amount; }
bool Player::spendGold(int amount) { if (gold >= amount) { gold -= amount; return true; } return false; }

void Player::equipArmor(Armor* armor) {
    if (equippedArmor != nullptr && equippedArmor->getMaxHpBonus() > 0) {
        maxHP -= equippedArmor->getMaxHpBonus();
        if (hp > maxHP) hp = maxHP;
    }
    equippedArmor = armor;
    if (armor->getMaxHpBonus() > 0) {
        maxHP += armor->getMaxHpBonus();
        hp += armor->getMaxHpBonus();
    }
}

void Player::equipWeapon(Weapon* newWeapon) {
    equippedWeapon = newWeapon;
}

string Player::getArmorName() const {
    if (equippedArmor == nullptr) {
        return "장착 안 함";
    }

    return equippedArmor->getName();
}

std::string Player::getWeaponName() const {
    if (equippedWeapon == nullptr)
        return "없음";

    return equippedWeapon->getName();
}

int Player::calculateAttackDamage(int baseDamage) const {
    int damage = status.calculateAttackDamage(baseDamage);

    if (equippedWeapon != nullptr) {
        damage += equippedWeapon->getAttackBonus();
    }

    return damage;
}

void Player::addVulnerable(int turn) {
    status.addVulnerable(turn);
    cout << "플레이어가 취약 " << turn << "을 얻었습니다.\n";
}

void Player::addWeak(int turn) {
    status.addWeak(turn);
    cout << "플레이어가 약화 " << turn << "을 얻었습니다.\n";
}
void Player::addItem(Item* item) {
    inventory.addItem(item);
}

bool Player::useItem(int index, Monster& target) {
    return inventory.useItem(index, *this, target);
}

void Player::showInventory() const {
    inventory.show(*this);
}

void Player::openInventory() {
    inventory.open(*this);
}

int Player::getPotionCount() const {
    return inventory.getPotionCount();
}

void Player::removeBlock(int amount) {
    if (amount < 0) {
        amount = 0;
    }

    block -= amount;

    if (block < 0) {
        block = 0;
    }
}