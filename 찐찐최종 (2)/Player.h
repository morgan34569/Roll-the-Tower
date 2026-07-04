#ifndef PLAYER_H
#define PLAYER_H
#include "Status.h"
#include "Inventory.h"
#include <vector>
#include <string>

class Item;
class Armor;
class Weapon;
class Monster;

class Player {
private:
    int hp, maxHP, block, gold, potionCount;
    Status status;
    Inventory inventory;
    Armor* equippedArmor;
    Weapon* equippedWeapon;

public:
    Player();
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHP; }
    int getBlock() const { return block; }
    int getGold() const { return gold; }
    int getPotionCount() const;
    Status& getStatus() { return status; }
    const Status& getStatus() const { return status; }

    void takeDamage(int damage);
    void takeDirectDamage(int damage);
    void applyPoisonBeforeAction();
    void applyBurnAfterAction();
    void heal(int amount);
    void addBlock(int amount);
    void removeBlock(int amount);
    bool spendGold(int amount);
    void addGold(int amount) { gold += amount; }

    void setHP(int v) { hp = v; }
    void setMaxHP(int v) { maxHP = v; }
    void setBlock(int v) { block = v; }
    void setGold(int v) { gold = v; }
    const Inventory& getInventory() const { return inventory; }

    void addItem(Item* item);
    bool useItem(int index, Monster& target);
    void showInventory() const;
    void openInventory();

    void equipArmor(Armor* armor);
    Armor* getEquippedArmor() const { return equippedArmor; }
    std::string getArmorName() const;
    Weapon* getEquippedWeapon() const { return equippedWeapon; }
    std::string getWeaponName() const;
    void equipWeapon(Weapon* newWeapon);

    int calculateAttackDamage(int baseDamage) const;
    void addVulnerable(int turn);
    void addWeak(int turn);

    void decreaseDebuffs() {
        status.decreaseDebuffs();
    }

    bool isDead() const { return hp <= 0; }
};

#endif