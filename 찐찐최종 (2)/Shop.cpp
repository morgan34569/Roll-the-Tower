#include "Shop.h"
#include "ItemStorage.h"
#include "Player.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

Shop::Shop() {}

static int getVisualLength(const string& str) {
    int len = 0;

    for (int i = 0; i < (int)str.size(); i++) {
        unsigned char c = str[i];

        // UTF-8 한글은 보통 3바이트이므로 화면 폭을 2칸으로 계산
        if ((c & 0xE0) == 0xE0) {
            len += 2;
            i += 2;
        }
        else {
            len += 1;
        }
    }

    return len;
}

void Shop::open(Player& player) {
    ItemStorage storage;

    vector<Item*> weapons;
    vector<Item*> armors;
    vector<Item*> potions;

    // 전체 아이템을 종류별로 분류
    for (int i = 0; i < storage.getCount(); i++) {
        Item* item = storage.getItem(i);
        int type = item->getCode() / 1000;

        if (type == 1) {
            weapons.push_back(item);
        }
        else if (type == 2) {
            armors.push_back(item);
        }
        else if (type == 3) {
            potions.push_back(item);
        }
    }

    // 랜덤 엔진
    random_device rd;
    mt19937 gen(rd());

    shuffle(weapons.begin(), weapons.end(), gen);
    shuffle(armors.begin(), armors.end(), gen);
    shuffle(potions.begin(), potions.end(), gen);

    // 이번 상점에서 판매할 아이템 목록
    vector<Item*> shopItems;

    // 테스트용: 1번은 무조건 화염도끼
    Item* fireAxe = nullptr;

    for (int i = 0; i < storage.getCount(); i++) {
        Item* item = storage.getItem(i);

        if (item->getCode() == 1002) {
            fireAxe = item;
            break;
        }
    }

    if (fireAxe != nullptr) {
        shopItems.push_back(fireAxe);
    }

    // 나머지 무기 1개 랜덤
    for (int i = 0; i < (int)weapons.size(); i++) {
        if (weapons[i]->getCode() != 1002) {
            shopItems.push_back(weapons[i]);
            break;
        }
    }

    // 방어구 2개
    for (int i = 0; i < 2 && i < (int)armors.size(); i++) {
        shopItems.push_back(armors[i]);
    }

    // 물약 6개
    for (int i = 0; i < 6 && i < (int)potions.size(); i++) {
        shopItems.push_back(potions[i]);
    }

    while (true) {
        system("cls");

        cout << "------------------------------- << 상점 >> -------------------------------\n\n";

        cout << "보유 골드 : " << player.getGold() << " G\n";
        cout << "장착 무기 : " << player.getWeaponName()
            << " | 장착 방어구 : " << player.getArmorName() << "\n\n";

        vector<Item*> weaponList;
        vector<Item*> armorList;
        vector<Item*> potionList;

        // 현재 남아있는 판매 아이템을 다시 종류별로 분리
        for (int i = 0; i < (int)shopItems.size(); i++) {
            int type = shopItems[i]->getCode() / 1000;

            if (type == 1) {
                weaponList.push_back(shopItems[i]);
            }
            else if (type == 2) {
                armorList.push_back(shopItems[i]);
            }
            else if (type == 3) {
                potionList.push_back(shopItems[i]);
            }
        }

        cout << "+--------------------------------+  +--------------------------------+  +--------------------------------+\n";
        cout << "|              무기              |  |             방어구             |  |              물약              |\n";
        cout << "+--------------------------------+  +--------------------------------+  +--------------------------------+\n";

        int maxSize = max({ (int)weaponList.size(), (int)armorList.size(), (int)potionList.size() });

        for (int i = 0; i < maxSize; i++) {
            string w = "";
            string a = "";
            string p = "";

            if (i < (int)weaponList.size()) {
                w = to_string(i + 1) + ". "
                    + weaponList[i]->getName()
                    + " (" + to_string(weaponList[i]->getPrice()) + "G)";
            }

            if (i < (int)armorList.size()) {
                a = to_string(i + 1 + (int)weaponList.size()) + ". "
                    + armorList[i]->getName()
                    + " (" + to_string(armorList[i]->getPrice()) + "G)";
            }

            if (i < (int)potionList.size()) {
                p = to_string(i + 1 + (int)weaponList.size() + (int)armorList.size()) + ". "
                    + potionList[i]->getName()
                    + " (" + to_string(potionList[i]->getPrice()) + "G)";
            }

            int wLen = getVisualLength(w);
            int aLen = getVisualLength(a);
            int pLen = getVisualLength(p);

            cout << "| " << w;
            for (int j = 0; j < 30 - wLen; j++) {
                cout << " ";
            }

            cout << " |  | " << a;
            for (int j = 0; j < 30 - aLen; j++) {
                cout << " ";
            }

            cout << " |  | " << p;
            for (int j = 0; j < 30 - pLen; j++) {
                cout << " ";
            }

            cout << " |\n";
        }

        cout << "+--------------------------------+  +--------------------------------+  +--------------------------------+\n\n";

        cout << "-------------------------------------------------------------------------\n";
        cout << "무엇을 사시겠습니까? (0 = 나가기)\n";
        cout << "-------------------------------------------------------------------------\n";
        cout << "입력 : ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice >(int)shopItems.size()) {
            cout << "\n잘못된 선택!\n";
            system("pause");
            continue;
        }

        Item* selected = shopItems[choice - 1];

        if (player.spendGold(selected->getPrice())) {
            player.addItem(selected->clone());

            cout << "\n" << selected->getName() << " 구매 완료!\n";

            // 구매한 아이템은 현재 상점 목록에서 제거
            shopItems.erase(shopItems.begin() + (choice - 1));
        }
        else {
            cout << "\n골드 부족!\n";
        }

        system("pause");
    }
}