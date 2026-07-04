#include "GameManager.h"
#include "SaveManager.h"
#include "Dice.h"
#include "Battle.h"
#include "Biomes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

int GameManager::getmoveCount() { return moveCount; }

int GameManager::setmoveCount(int NUM) { return moveCount = NUM; }

// [추가] 몬스터 보상 함수
void GameManager::giveMonsterReward(Player& player) {
    map.monsterReward(player);
}

// GameManager 생성자
GameManager::GameManager()
    : diceValue(0), moveCount(0), diceChance(10), isRunning(true), currentStage(1), map() {
}

GameManager::GameManager(bool loadMode)
    : diceValue(0), moveCount(0), diceChance(10), isRunning(true), currentStage(1), map(loadMode) {
}

void GameManager::start() {
    while (isRunning && !player.isDead()) {
        printGameScreen();
        char input;
        cout << "\n입력 (W/A/S/D:이동, R:주사위, I:아이템, Q:종료): ";
        cin >> input;
        handleInput(input);
    }

    if (player.isDead()) {
        cout << "\n플레이어가 쓰러졌습니다... 게임 오버!\n";
    }
    else {
        cout << "\n게임 종료\n";
    }
}

void GameManager::printGameScreen() const {
    system("cls");

    vector<string> mapLines = map.getMapLines();
    vector<string> rightLines;

    rightLines.push_back("--- [ 현재 상태 ] ---");
    rightLines.push_back("현재 지형: " + map.getBiome()->getName());
    rightLines.push_back("남은 이동 횟수: " + to_string(moveCount));
    rightLines.push_back("");
    rightLines.push_back("M : 몬스터");
    rightLines.push_back("S : 상점");
    rightLines.push_back("B : 보스");
    rightLines.push_back("E : 이벤트");
    rightLines.push_back(". : 빈방");
    rightLines.push_back("P : 플레이어");
    rightLines.push_back("");
    rightLines.push_back("보유 골드 : "+ to_string(player.getGold()));
    rightLines.push_back("");
    rightLines.push_back("주사위");

    printDiceImageLines(diceValue, rightLines);

    size_t maxLines = max(mapLines.size(), rightLines.size());
    size_t mapWidth = (mapLines.empty()) ? 0 : mapLines[0].length();

    for (size_t i = 0; i < maxLines; i++) {
        if (i < mapLines.size()) {
            cout << mapLines[i];
        }
        else {
            cout << string(mapWidth, ' ');
        }
        cout << "    ";
        if (i < rightLines.size()) {
            cout << rightLines[i];
        }
        cout << "\n";
    }
}

void GameManager::handleInput(char input) {
    // [수정] static_cast<char> 적용
    input = static_cast<char>(tolower(input));

    if (input == 'r') {
        if (moveCount == 0) {
            rollDice();
            system("pause");
        }
        else {
            cout << "\n아직 이동 횟수가 남았습니다!\n";
            system("pause");
        }
    }
    else if (input == 'i') {
        player.openInventory();
    }
    else if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
        movePlayer(input);
    }
    else if (input == 'q') {
        cout << "\n게임을 저장하고 종료하시겠습니까? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            SaveManager::saveGame(*this);
            isRunning = false;
        }
    }
}

void GameManager::rollDice() {
    diceValue = Dice::roll();

    map.getBiome()->onDiceRoll(player);

    if (player.isDead()) {
        isRunning = false;
        return;
    }

    moveCount = map.getBiome()->modifyDiceRoll(diceValue);

    if (moveCount < 0) {
        moveCount = 0;
    }
}

void GameManager::movePlayer(char input) {
    if (moveCount <= 0) {
        cout << "\n주사위를 먼저 굴려주세요!\n";
        system("pause");
        return;
    }

    int dx = 0, dy = 0;
    if (input == 'w') dy = -1;
    else if (input == 's') dy = 1;
    else if (input == 'a') dx = -1;
    else if (input == 'd') dx = 1;

    if (map.movePlayerOneStep(dx, dy)) {
        moveCount--;
        map.getBiome()->onStep(player);
        if (player.isDead()) {
            isRunning = false;
            return;
        }
        handleTileEvent();
    }
    else {
        cout << "\n막힌 길입니다!\n";
        system("pause");
    }
}

void GameManager::handleTileEvent() {
    char tile = map.getCurrentTile();

    if (tile == 'M') {
        bool isAlive = Battle::startMonsterBattle(player, map.getBiome(), currentStage);

        if (!isAlive) {
            isRunning = false;
        }
        else {
            // [추가] 몬스터 도망 처리 로직
            if (Battle::didLastMonsterEscape()) {
                cout << "\n몬스터가 도망쳐 보상을 얻지 못했습니다.\n";
                system("pause");
                map.clearCurrentTile();
            }
            else {
                map.monsterReward(player);
                map.clearCurrentTile();
            }
        }
        return;
    }

    if (tile == 'S') {
        map.openShop(player);
        map.clearCurrentTile();
        return;
    }

    if (tile == 'E') {
        system("pause");
        map.openEvent(player, *map.getBiome(), *this);
        map.clearCurrentTile();
        return;
    }

    if (tile == 'B') {
        if (map.getBiome()->getName() != "평원") {
            cout << "\n장수말벌은 평원에서만 등장합니다!\n";
            system("pause");
            return;
        }

        bool isAlive = Battle::startBossBattle(player, map.getBiome());

        if (!isAlive) {
            isRunning = false;
        }
        else {
            cout << "\n장수말벌을 처치했습니다!\n";
            system("pause");

            // [추가] 보스 처치 후 보상 및 다음 맵 이동
            map.bossReward(player);
            map.startNextMap();
            moveCount = 0;
            diceValue = 0;

            currentStage++;
            cout << "\n======================================================\n";
            cout << " ★★★ " << currentStage << " 스테이지로 진입합니다! 적들이 더욱 흉포해집니다! ★★★\n";
            cout << "======================================================\n";
            system("pause");
        }
        return;
    }
}

void GameManager::printDiceImageLines(int value, vector<string>& lines) const {
    lines.push_back("+-------+");

    if (value == 1) {
        lines.push_back("|       |");
        lines.push_back("|   o   |");
        lines.push_back("|       |");
    }
    else if (value == 2) {
        lines.push_back("| o     |");
        lines.push_back("|       |");
        lines.push_back("|     o |");
    }
    else if (value == 3) {
        lines.push_back("| o     |");
        lines.push_back("|   o   |");
        lines.push_back("|     o |");
    }
    else if (value == 4) {
        lines.push_back("| o   o |");
        lines.push_back("|       |");
        lines.push_back("| o   o |");
    }
    else if (value == 5) {
        lines.push_back("| o   o |");
        lines.push_back("|   o   |");
        lines.push_back("| o   o |");
    }
    else if (value >= 6) {
        lines.push_back("| o   o |");
        lines.push_back("| o   o |");
        lines.push_back("| o   o |");
    }
    else {
        lines.push_back("|       |");
        lines.push_back("|       |");
        lines.push_back("|       |");
    }
    lines.push_back("+-------+");
}