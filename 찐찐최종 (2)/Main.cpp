#include "GameManager.h"
#include "Inventory.h"
#include "SaveManager.h"
#include "Intro.h"
#include <Windows.h>

int main() {
    int choice = showIntro();

    if (choice == 1) {
        // 새로 시작 → 기본 생성자 호출 (바이옴 선택 UI 포함)
        GameManager gm;
        gm.start();
    }
    else if (choice == 2) {
        // 불러오기 → loadMode 생성자 호출 (바이옴 선택 스킵)
        GameManager gm(true);
        if (SaveManager::saveExists()) {
            SaveManager::loadGame(gm);
        }
        else {
            cout << "세이브 파일이 없습니다. 새 게임을 시작합니다.\n";
            system("pause");
            GameManager newGame;  // 바이옴 선택 포함 새 게임
            newGame.start();
            return 0;
        }
        gm.start();
    }

    return 0;
}
