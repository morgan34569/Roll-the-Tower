#include "GameManager.h"
#include "Inventory.h"
#include "SaveManager.h"
#include "Intro.h"
#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
    bool autoLoad = false; // 1번(이어하기)을 눌렀을 때 타이틀 화면을 건너뛰고 바로 세이브를 불러오기 위한 장치

    while (true) {
        int choice;

        if (autoLoad) {
            choice = 2; // 세이브 로드 선택지로 강제 지정
            autoLoad = false; // 사용 후 다시 초기화
        }
        else {
            choice = showIntro(); // 평소에는 정상적으로 타이틀 출력
        }

        GameManager* gm = nullptr;

        if (choice == 1) {
            // 새로 시작
            gm = new GameManager();
        }
        else if (choice == 2) {
            // 불러오기
            gm = new GameManager(true);
            if (SaveManager::saveExists()) {
                SaveManager::loadGame(*gm);
            }
            else {
                cout << "세이브 파일이 없습니다. 새 게임을 시작합니다.\n";
                system("pause");
                delete gm;
                gm = new GameManager();
            }
        }

        // 게임 본편 실행
        gm->start();

        bool restart = false;

        // 1. 게임을 클리어하고 종료된 경우
        if (gm->isGameCleared()) {
            showEnding();
            delete gm;
            break;
        }
        // 2. 플레이어가 사망하여 게임 오버된 경우
        else if (gm->getPlayer().isDead()) {
            int overChoice = showGameOver();

            if (overChoice == 1) {
                // 1번: 마지막 세이브 로드 (이어하기)
                autoLoad = true;
                restart = true;
            }
            else if (overChoice == 2) {
                // 2번: 타이틀로 돌아가기 (새로 시작)
                autoLoad = false;
                restart = true;
            }
            else {
                // 3번: 게임 종료
                restart = false;
            }
        }

        // 메모리 해제
        delete gm;

        // 종료를 선택했거나 정상 종료(q 버튼) 시 루프 탈출
        if (!restart) {
            break;
        }
    }

    return 0;
}