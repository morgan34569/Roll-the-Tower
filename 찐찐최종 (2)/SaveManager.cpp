#include "SaveManager.h"
#include "GameManager.h"
#include "Player.h"
#include "TileMap.h"
#include "ItemStorage.h"
#include "Weapon.h"
#include "Armor.h"
#include <iostream>
#include <sstream>

using namespace std;

const string SaveManager::SAVE_FILE = "save.dat";

bool SaveManager::saveExists() {
    ifstream f(SAVE_FILE);
    return f.good();
}

bool SaveManager::saveGame(const GameManager& gm) {
    const Player& player = gm.getPlayer();
    const TileMap& tileMap = gm.getMap();

    ofstream out(SAVE_FILE);
    if (!out.is_open()) {
        cout << "세이브 파일을 열 수 없습니다.\n";
        return false;
    }

    out << "[GameManager]\n";
    out << "currentStage=" << gm.getCurrentStage() << "\n";
    out << "moveCount=" << gm.getMoveCount() << "\n";
    out << "diceValue=" << gm.getDiceValue() << "\n";

    out << "[Player]\n";
    out << "hp=" << player.getHP() << "\n";
    out << "maxHP=" << player.getMaxHP() << "\n";
    out << "block=" << player.getBlock() << "\n";
    out << "gold=" << player.getGold() << "\n";

    const Status& st = player.getStatus();
    out << "[Status]\n";
    out << "strength=" << st.getStrength() << "\n";
    out << "vulnerable=" << st.getVulnerable() << "\n";
    out << "weak=" << st.getWeak() << "\n";
    out << "poison=" << st.getPoison() << "\n";
    out << "parasite=" << st.getParasite() << "\n";

    out << "[Equipment]\n";
    Weapon* w = player.getEquippedWeapon();
    out << "weaponCode=" << (w ? w->getCode() : 0) << "\n";
    Armor* a = player.getEquippedArmor();
    out << "armorCode=" << (a ? a->getCode() : 0) << "\n";

    const Inventory& inv = player.getInventory();
    out << "[Inventory]\n";
    out << "count=" << inv.getCount() << "\n";
    for (int i = 0; i < inv.getCount(); i++) {
        out << "item=" << inv.getItem(i)->getCode() << "\n";
    }

    out << "[TileMap]\n";
    out << "playerX=" << tileMap.getPlayerX() << "\n";
    out << "playerY=" << tileMap.getPlayerY() << "\n";
    out << "biomeIndex=" << tileMap.getBiomeIndex() << "\n";

    out << "map=";
    for (int y = 0; y < TileMap::SIZE; y++)
        for (int x = 0; x < TileMap::SIZE; x++)
            out << tileMap.getTile(x, y);
    out << "\n";

    out.close();
    cout << "게임이 저장되었습니다.\n";
    return true;
}


bool SaveManager::loadGame(GameManager& gm) {
    Player& player = gm.getPlayer();
    TileMap& tileMap = gm.getMap();

    ifstream in(SAVE_FILE);
    if (!in.is_open()) {
        cout << "세이브 파일이 없습니다.\n";
        return false;
    }

    ItemStorage storage;

    string line;
    string section;

    while (getline(in, line)) {
        if (line.empty()) continue;

        if (line[0] == '[') {
            section = line;
            continue;
        }

        auto sep = line.find('=');
        if (sep == string::npos) continue;
        string key = line.substr(0, sep);
        string val = line.substr(sep + 1);

        if (section == "[GameManager]") {
            if (key == "currentStage") gm.setCurrentStage(stoi(val));
            else if (key == "moveCount")    gm.setMoveCount(stoi(val));
            else if (key == "diceValue")    gm.setDiceValue(stoi(val));
        }

        else if (section == "[Player]") {
            if (key == "hp")    player.setHP(stoi(val));
            else if (key == "maxHP") player.setMaxHP(stoi(val));
            else if (key == "block") player.setBlock(stoi(val));
            else if (key == "gold")  player.setGold(stoi(val));
        }

        else if (section == "[Status]") {
            Status& st = player.getStatus();
            if (key == "strength")   st.setStrength(stoi(val));
            else if (key == "vulnerable") st.setVulnerable(stoi(val));
            else if (key == "weak")       st.setWeak(stoi(val));
            else if (key == "poison")     st.setPoison(stoi(val));
            else if (key == "parasite")   st.setParasite(stoi(val));
        }

        else if (section == "[Equipment]") {
            if (key == "weaponCode") {
                int code = stoi(val);
                if (code != 0) {
                    Item* found = storage.findByCode(code);
                    if (found) player.equipWeapon(static_cast<Weapon*>(found->clone()));
                }
            }
            else if (key == "armorCode") {
                int code = stoi(val);
                if (code != 0) {
                    Item* found = storage.findByCode(code);
                    if (found) player.equipArmor(static_cast<Armor*>(found->clone()));
                }
            }
        }

        else if (section == "[Inventory]") {
            if (key == "item") {
                int code = stoi(val);
                Item* found = storage.findByCode(code);
                if (found) player.addItem(found->clone());
            }
        }

        else if (section == "[TileMap]") {
            if (key == "playerX")    tileMap.setPlayerPos(stoi(val), tileMap.getPlayerY());
            else if (key == "playerY")    tileMap.setPlayerPos(tileMap.getPlayerX(), stoi(val));
            else if (key == "biomeIndex") tileMap.loadBiome(stoi(val));
            else if (key == "map")        tileMap.loadMapString(val);
        }
    }

    in.close();
    cout << "게임을 불러왔습니다.\n";
    return true;
}