#include "TileMap.h"
#include "Biomes.h"
#include "Event.h"
#include "ItemStorage.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==========================================
// BiomeIndex enum (1번 코드에서 추가)
// ==========================================
enum BiomeIndex {
    BIOME_NORMAL = 0,          // 평원
    BIOME_SNOWFIELD = 1,       // 설원
    BIOME_VOLCANO = 2,         // 화산
    BIOME_OCEAN = 3,           // 바다
    BIOME_DESERT = 4,          // 사막
    BIOME_ANCIENT_ARMORY = 5,  // 고대의 무기고
    BIOME_THUNDEROUS_PEAK = 6, // 벼락 맞은 골짜기
    BIOME_ABYSS = 7            // 심연
};

static Biome* createBiomeByIndex(int index) {
    if (index == BIOME_NORMAL)           return new NormalBiome();
    else if (index == BIOME_SNOWFIELD)   return new Snowfield();
    else if (index == BIOME_VOLCANO)     return new Volcano();
    else if (index == BIOME_OCEAN)       return new Ocean();
    else if (index == BIOME_DESERT)      return new Desert();
    else if (index == BIOME_ABYSS)       return new Abyss();
    else if (index == BIOME_THUNDEROUS_PEAK) return new ThunderousPeak();
    else                                 return new AncientArmory();
}

// ==========================================
// 내부 헬퍼 함수들 (1번 코드에서 추가)
// ==========================================

void TileMap::setupNewMap() {
    initMap();
    generateMap();

    playerX = SIZE / 2;
    playerY = SIZE / 2;

    char startTile = map[playerY][playerX];

    if (startTile == 'B' || startTile == 'S' || startTile == 'E') {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                if (map[y][x] == '.' || map[y][x] == 'M') {
                    swap(map[playerY][playerX], map[y][x]);
                    y = SIZE;
                    break;
                }
            }
        }
    }

    applyBiomeTileOverrides();
}

void TileMap::applyBiomeTileOverrides() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (map[y][x] == 'B') continue;
            map[y][x] = currentBiome->getTileOverride(map[y][x]);
        }
    }
}

vector<int> TileMap::makeNextBiomeChoiceIndexes() const {
    vector<int> choices;

    // 세 번째 보스까지 클리어하면 마지막 선택지는 심연만
    if (bossClearCount >= 3) {
        choices.push_back(BIOME_ABYSS);
        return choices;
    }

    // 평원 클리어 후부터 나오는 중간 맵 후보 6개
    int pool[6] = {
        BIOME_SNOWFIELD,
        BIOME_VOLCANO,
        BIOME_OCEAN,
        BIOME_DESERT,
        BIOME_ANCIENT_ARMORY,
        BIOME_THUNDEROUS_PEAK
    };

    for (int i = 0; i < 6; i++) {
        int biomeIndex = pool[i];
        if (find(clearedBiomeIndexes.begin(), clearedBiomeIndexes.end(), biomeIndex)
            == clearedBiomeIndexes.end()) {
            choices.push_back(biomeIndex);
        }
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(choices.begin(), choices.end(), gen);

    if (choices.size() > 3) {
        choices.resize(3);
    }

    return choices;
}

// ==========================================
// 기본 생성자 (1번 방식: 첫 진입 평원 고정)
// ==========================================
TileMap::TileMap() {
    srand((unsigned int)time(nullptr));
    gold = 100;

    bossClearCount = 0;
    clearedBiomeIndexes.clear();

    currentBiomeIndex = BIOME_NORMAL;
    currentBiome = createBiomeByIndex(currentBiomeIndex);

    int selection = 0;

    while (true) {
        system("cls");
        cout << "=========================================\n";
        cout << "         새로운 모험의 시작지 선택        \n";
        cout << "=========================================\n";
        cout << "첫 진입 지형은 평원으로 고정됩니다.\n\n";
        cout << "1. " << currentBiome->getName() << "\n";
        cout << "=========================================\n";
        cout << "선택 (1): ";
        cin >> selection;

        if (selection == 1) break;

        cout << "\n잘못된 선택입니다! 다시 입력해주세요.\n";
        system("pause");
    }

    cout << "\n[" << currentBiome->getName() << "] 지형으로 진입합니다!\n";
    system("pause");

    setupNewMap();
}

// ==========================================
// 로드 전용 생성자 (2번 코드에서 유지)
// ==========================================
TileMap::TileMap(bool loadMode) {
    srand((unsigned int)time(nullptr));
    gold = 100;
    bossClearCount = 0;
    clearedBiomeIndexes.clear();
    currentBiomeIndex = BIOME_NORMAL;
    currentBiome = new NormalBiome(); // 임시, loadBiome()으로 곧 덮어씌워짐
    initMap();
    playerX = SIZE / 2;
    playerY = SIZE / 2;
    // generateMap() 안 함 - loadMapString()으로 복원
}

TileMap::~TileMap() {
    delete currentBiome;
}

void TileMap::initMap() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            map[y][x] = '.';
        }
    }
}

void TileMap::generateMap() {
    vector<char> rooms;

    for (int i = 0; i < 16; i++) rooms.push_back('M');
    for (int i = 0; i < 4; i++)  rooms.push_back('S');

    rooms.push_back('B');

    for (int i = 0; i < 8; i++) rooms.push_back('E');

    while (rooms.size() < SIZE * SIZE) {
        rooms.push_back('.');
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(rooms.begin(), rooms.end(), gen);

    int idx = 0;
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            map[y][x] = rooms[idx++];
        }
    }
}

// ==========================================
// 세이브/로드용 함수들 (2번 코드에서 유지)
// ==========================================

int TileMap::getBiomeIndex() const {
    return currentBiomeIndex;
}

void TileMap::loadBiome(int index) {
    delete currentBiome;
    currentBiomeIndex = index;
    currentBiome = createBiomeByIndex(index);
}

void TileMap::loadMapString(const std::string& s) {
    int idx = 0;
    for (int y = 0; y < SIZE; y++)
        for (int x = 0; x < SIZE; x++)
            map[y][x] = s[idx++];
}

// ==========================================
// 공통 함수들
// ==========================================

std::vector<std::string> TileMap::getMapLines() const {
    vector<string> lines;

    for (int y = 0; y < SIZE; y++) {
        string line = "";
        for (int x = 0; x < SIZE; x++) {
            if (x == playerX && y == playerY) line += "P ";
            else line += string(1, map[y][x]) + " ";
        }
        lines.push_back(line);
    }

    return lines;
}

bool TileMap::movePlayerOneStep(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (newX < 0 || newX >= SIZE || newY < 0 || newY >= SIZE) return false;

    playerX = newX;
    playerY = newY;

    return true;
}

char TileMap::getCurrentTile() const {
    return map[playerY][playerX];
}

void TileMap::clearCurrentTile() {
    map[playerY][playerX] = '.';
}

int TileMap::getPlayerX() const { return playerX; }
int TileMap::getPlayerY() const { return playerY; }
int TileMap::getGold()    const { return gold; }

const char* TileMap::getTileName(char tile) const {
    switch (tile) {
    case 'M': return "몬스터 방";
    case 'S': return "상점";
    case 'B': return "보스방";
    case 'E': return "이벤트 방";
    case '.': return "빈 방";
    default:  return "알 수 없음";
    }
}

void TileMap::openEvent(Player& player, Biome& biome, GameManager& gm) {
    Event event;
    event.EventOpen(player, &biome, gm);
}

void TileMap::openShop(Player& player) {
    shop.open(player);
}

void TileMap::monsterReward(Player& player) {
    cout << "\n===== 몬스터 처치 보상 =====\n";

    int baseGold = rand() % 51 + 50;
    int rewardGold = static_cast<int>(baseGold * currentBiome->getGoldMultiplier());

    cout << "골드 보상: " << rewardGold << " G\n";
    cout << "받으시겠습니까? (y/n): ";

    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        player.addGold(rewardGold);
        cout << "골드를 획득했습니다.\n";
        cout << "현재 골드: " << player.getGold() << " G\n";
    }
    else {
        cout << "골드를 받지 않았습니다.\n";
    }

    if (rand() % 100 < 20) {
        ItemStorage storage;
        vector<Item*> potionList;

        for (int i = 0; i < storage.getCount(); i++) {
            Item* item = storage.getItem(i);
            if (item->getCode() / 1000 == 3) potionList.push_back(item);
        }

        if (!potionList.empty()) {
            int randomIndex = rand() % potionList.size();
            Item* rewardPotion = potionList[randomIndex];

            cout << "\n포션이 드랍되었습니다.\n";
            cout << "드랍 포션: " << rewardPotion->getName() << "\n";
            cout << "받으시겠습니까? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                player.addItem(rewardPotion->clone());
                cout << rewardPotion->getName() << "을(를) 획득했습니다.\n";
            }
            else {
                cout << "포션을 받지 않았습니다.\n";
            }
        }
        else {
            cout << "\n드랍 가능한 포션이 없습니다.\n";
        }
    }
    else {
        cout << "\n포션은 드랍되지 않았습니다.\n";
    }

    system("pause");
}

void TileMap::bossReward(Player& player) {
    cout << "\n===== 보스 클리어 보상 =====\n";

    int baseGold = rand() % 51 + 50;
    int rewardGold = static_cast<int>(baseGold * currentBiome->getGoldMultiplier() * 2.0f);

    player.addGold(rewardGold);

    cout << "보스 처치 보상으로 골드 " << rewardGold << " G를 획득했습니다.\n";
    cout << "현재 골드: " << player.getGold() << " G\n";

    ItemStorage storage;
    vector<Item*> weapons;

    for (int i = 0; i < storage.getCount(); i++) {
        Item* item = storage.getItem(i);
        if (item->getCode() / 1000 == 1 && item->getCode() != 1001)
            weapons.push_back(item);
    }

    if (!weapons.empty()) {
        int randomIndex = rand() % weapons.size();
        Item* rewardWeapon = weapons[randomIndex];
        player.addItem(rewardWeapon->clone());
        cout << "랜덤 무기 보상: " << rewardWeapon->getName() << " 획득!\n";
    }
    else {
        cout << "보상으로 지급할 무기가 없습니다.\n";
    }

    system("pause");
}

// ==========================================
// startNextMap (1번 방식: 클리어 기록 기반)
// ==========================================
void TileMap::startNextMap() {
    // 현재 맵을 클리어 목록에 저장
    if (find(clearedBiomeIndexes.begin(), clearedBiomeIndexes.end(), currentBiomeIndex)
        == clearedBiomeIndexes.end()) {
        clearedBiomeIndexes.push_back(currentBiomeIndex);
    }

    bossClearCount++;

    system("cls");

    cout << "=========================================\n";
    cout << "              맵 클리어!                 \n";
    cout << "=========================================\n";
    cout << "보스를 처치하여 현재 맵을 클리어했습니다.\n";

    vector<int> choiceIndexes = makeNextBiomeChoiceIndexes();

    if (choiceIndexes.empty()) {
        cout << "더 이상 진입할 수 있는 지형이 없습니다.\n";
        system("pause");
        return;
    }

    cout << "다음으로 진입할 지형을 선택하세요.\n\n";

    vector<Biome*> choices;

    for (size_t i = 0; i < choiceIndexes.size(); i++) {
        Biome* biome = createBiomeByIndex(choiceIndexes[i]);
        choices.push_back(biome);
        cout << i + 1 << ". " << biome->getName() << "\n";
    }

    int selection = 0;

    while (true) {
        cout << "\n선택 (1~" << choices.size() << "): ";
        cin >> selection;

        if (selection >= 1 && selection <= static_cast<int>(choices.size())) break;

        cout << "잘못된 선택입니다. 다시 입력하세요.\n";
    }

    delete currentBiome;

    currentBiomeIndex = choiceIndexes[selection - 1];
    currentBiome = choices[selection - 1];

    for (size_t i = 0; i < choices.size(); i++) {
        if (i != static_cast<size_t>(selection - 1)) {
            delete choices[i];
        }
    }

    setupNewMap();

    cout << "\n[" << currentBiome->getName() << "] 지형으로 이동합니다!\n";
    system("pause");
}