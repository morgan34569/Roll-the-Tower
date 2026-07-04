#include "Inventory.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Monster.h"
#include "Battle.h"
#include "Player.h"
#include <iostream>
#include <map>

using namespace std;

Inventory::Inventory() {}

Inventory::~Inventory() {
    for (Item* item : items) {
        delete item;
    }
}

void Inventory::addItem(Item* item) {
    items.push_back(item);
}

int Inventory::getCount() const {
    return (int)items.size();
}

Item* Inventory::getItem(int index) const {
    return items[index];
}

int Inventory::getPotionCount() const {
    int count = 0;

    for (Item* item : items) {
        if (item->getCode() / 1000 == 3) {
            count++;
        }
    }

    return count;
}

void Inventory::show(const Player& player) const {
    cout << "\n========= 인벤토리 =========\n";
    cout << "현재무기: " << player.getWeaponName() << "\n";
    cout << "현재 방어구: " << player.getArmorName() << "\n";
    cout << "현재 보유 포션: ";
    showPotionNamesWithCount();
    cout << "\n\n";

    if (items.empty()) {
        cout << "보유한 아이템이 없습니다.\n";
        return;
    }

    for (int i = 0; i < (int)items.size(); i++) {
        cout << i + 1 << ". " << items[i]->getName();

        int type = items[i]->getCode() / 1000;

        if (type == 1) {
            Weapon* weapon = (Weapon*)items[i];
            cout << " [무기]";

            if (player.getEquippedWeapon() == weapon) {
                cout << " [장착중]";
            }
        }
        else if (type == 2) {
            cout << " [방어구]";

            if (player.getEquippedArmor() == items[i]) {
                cout << " [장착중]";
            }
        }

        cout << "\n";
    }
}

void Inventory::showPotionNamesWithCount() const {
    map<string, int> countMap;

    for (Item* item : items) {
        if (item->getCode() / 1000 == 3) {
            countMap[item->getName()]++;
        }
    }

    if (countMap.empty()) {
        cout << "없음";
        return;
    }

    bool first = true;

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        if (!first) {
            cout << ", ";
        }

        cout << it->first << " * " << it->second;
        first = false;
    }

    cout << "\n";
}

bool Inventory::useItem(int index, Player& player, Monster& target) {
    if (index < 0 || index >= (int)items.size()) {
        cout << "잘못된 번호입니다.\n";
        return false;
    }

    Item* selected = items[index];
    int type = selected->getCode() / 1000;

    selected->Use(player, target);

    if (type == 3) {
        delete selected;
        items.erase(items.begin() + index);
        return false;
    }

    return true;
}

void Inventory::open(Player& player) {
    while (true) {
        system("cls");

        show(player);

        cout << "\n0. 나가기\n";
        cout << "사용/장착할 아이템 번호: ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice >(int)items.size()) {
            cout << "잘못된 번호입니다.\n";
            system("pause");
            continue;
        }

        Monster* dummy = Battle::createRandomMonster();

        useItem(choice - 1, player, *dummy);

        delete dummy;

        system("pause");
    }
}