#include "Event.h"
#include "ItemStorage.h"
#include "Player.h"
#include "Battle.h"
#include "GameManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Event::Event() {}

void Event::EventOpen(Player& player, Biome* biome, GameManager& gm) {
    system("cls");
    srand(static_cast<unsigned int>(time(0)));

    cout << "당신은 왠지 모르게 음산한 기운이 흐르는 장소에 도착했습니다.\n";
    getchar();

    for (int i = 0; i < 3; i++) {
        cout << "당신은 앞으로 나아갑니다. \n";
        cout << "... \n";
        getchar();
        system("cls");
    }

    int EventNum = rand() % 11;

    if (EventNum <= 6) {
        cout << "갑작스럽게 몬스터가 튀어 나왔다!\n";
        getchar();
        system("cls");
        Battle::startMonsterBattle(player, biome, gm.getCurrentStage());
    }
    else if (EventNum <= 8) {
        cout << "보물상자를 발견했다. 열어볼까? (Y/N)\n";
        char answer;
        cin >> answer;
        system("cls");
        if (answer == 'Y' || answer == 'y') {
            cout << "보물상자를 열었다!\n";
            ItemStorage storage;

            int randomIndex = rand() % storage.getCount();
            Item* randomItem = storage.getItem(randomIndex);

            // 아이템이 정상적으로 존재하면
            if (randomItem != nullptr) {
                // clone()으로 복사해서 플레이어 인벤토리에 추가
                player.addItem(randomItem->clone());

                // 획득 메시지 출력
                cout << randomItem->getName() << "을(를) 얻었다!\n";
                system("pause");
            }

        }
        else if (answer == 'N' || answer == 'n') {
            cout << "보물상자를 열지 않았다.\n";
            getchar();
        }
        else {
            cout << "잘못된 입력입니다.\n";
        }
    }
    else {
        cout << "당신은 함정에 빠졌습니다!\n\n";
        cout << "이동 횟수가 3 줄어 듭니다.";
        getchar();

        int CurMC = gm.getmoveCount();

        if (CurMC < 3)
            CurMC = 0;
        else
            CurMC -= 3;

        gm.setmoveCount(CurMC);
    }
}
