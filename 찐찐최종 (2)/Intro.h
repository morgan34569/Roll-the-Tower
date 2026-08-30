#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void getConsoleSize(int& width, int& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// 반환값: 1 = 새로 시작하기, 2 = 불러오기
int showIntro() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);
    system("cls");

    int artWidth = 95;
    int startX = 8 + ((consoleWidth - artWidth) / 2);
    int startY = 6;

    gotoxy(startX, startY + 0);
    cout << u8"████   ███  █     █        █████ █   █ █████    █████  ███  █   █ █████ ████    ";

    gotoxy(startX, startY + 1);
    cout << u8"█░░░█ █ ░░█ █░    █░        ░█░░░█░  █░█░░░░░    ░█░░░█ ░░█ █░  █░█░░░░░█░░░█   ";

    gotoxy(startX, startY + 2);
    cout << u8"████░░█░ ░█░█░░   █░░        █░░░█████░████░░░    █░░░█░ ░█░█░█ █░████░░████░░  ";

    gotoxy(startX, startY + 3);
    cout << u8"█░░█░ █░░ █░█░░   █░░        █░░ █░░░█░█░░░░      █░░ █░░ █░██░██░█░░░░ █░░█░ ░ ";

    gotoxy(startX, startY + 4);
    cout << u8"█░░░█░ ███ ░█████ █████      █░░ █░░░█░█████░     █░░  ███ ░█░░ █░█████░█░░░█░  ";

    gotoxy(startX, startY + 5);
    cout << u8" ░░  ░  ░░░ ░░░░░░ ░░░░░      ░░  ░░  ░░░░░░░      ░░   ░░░ ░░░░ ░░░░░░░ ░░  ░  ";

    gotoxy(startX, startY + 6);
    cout << u8"  ░   ░  ░░░  ░░░░░ ░░░░░      ░   ░   ░ ░░░░░      ░    ░░░  ░   ░ ░░░░░ ░   ░ ";


    // 메뉴 옵션
    const char* menu1 = "[ 1 ] 새로 시작하기";
    const char* menu2 = "[ 2 ] 불러오기";

    int menuY = consoleHeight - 6;
    int menu1X = (consoleWidth - 20) / 2;
    int menu2X = (consoleWidth - 14) / 2;

    gotoxy(menu1X, menuY);
    cout << menu1;
    gotoxy(menu2X, menuY + 2);
    cout << menu2;

    // 1 또는 2 입력 대기
    while (true) {
        char key = _getch();
        if (key == '1') {
            system("cls");
            return 1;
        }
        else if (key == '2') {
            system("cls");
            return 2;
        }
    }
}


void showEnding() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    system("cls");
    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);

    int artWidth = 87;
    int startX = (consoleWidth - artWidth) / 2;
    if (startX < 0) startX = 0;
    int startY = 8;

    // GAME CLEAR 아스키 아트
    gotoxy(startX, startY + 0); cout << u8" ██████   █████  ███    ███ ███████     ██████ ██      ███████  █████  ██████  ";
    gotoxy(startX, startY + 1); cout << u8"██       ██   ██ ████  ████ ██         ██      ██      ██      ██   ██ ██   ██ ";
    gotoxy(startX, startY + 2); cout << u8"██   ███ ███████ ██ ████ ██ █████      ██      ██      █████   ███████ ██████  ";
    gotoxy(startX, startY + 3); cout << u8"██    ██ ██   ██ ██  ██  ██ ██         ██      ██      ██      ██   ██ ██   ██ ";
    gotoxy(startX, startY + 4); cout << u8" ██████  ██   ██ ██      ██ ███████     ██████ ███████ ███████ ██   ██ ██   ██ ";

    const char* msg1 = "★★★ 축하합니다! 심연의 군주를 물리치고 세상을 구했습니다! ★★★";
    const char* msg2 = "아무 키나 누르면 게임이 종료됩니다...";

    gotoxy((consoleWidth - 65) / 2, startY + 8);
    cout << msg1;

    gotoxy((consoleWidth - 35) / 2, startY + 10);
    cout << msg2;

    _getch(); // 사용자가 아무 키나 누를 때까지 대기
}

// 반환값: 1 = 세이브 불러오기(이어하기), 2 = 타이틀로 돌아가기, 3 = 종료
int showGameOver() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    system("cls");
    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);

    int artWidth = 73;
    int startX = (consoleWidth - artWidth) / 2;
    if (startX < 0) startX = 0;
    int startY = 8;

    // GAME OVER 아스키 아트
    gotoxy(startX, startY + 0); cout << u8" ██████   █████  ███    ███ ███████     ██████  ██    ██ ███████ ██████  ";
    gotoxy(startX, startY + 1); cout << u8"██       ██   ██ ████  ████ ██         ██    ██ ██    ██ ██      ██   ██ ";
    gotoxy(startX, startY + 2); cout << u8"██   ███ ███████ ██ ████ ██ █████      ██    ██ ██    ██ █████   ██████  ";
    gotoxy(startX, startY + 3); cout << u8"██    ██ ██   ██ ██  ██  ██ ██         ██    ██  ██  ██  ██      ██   ██ ";
    gotoxy(startX, startY + 4); cout << u8" ██████  ██   ██ ██      ██ ███████     ██████    ████   ███████ ██   ██ ";

    // 3가지 옵션으로 텍스트 변경
    const char* msg = "[ 1 ] 마지막 저장 시점 불러오기    [ 2 ] 타이틀로 돌아가기    [ 3 ] 게임 종료";

    gotoxy((consoleWidth - 76) / 2, startY + 8);
    cout << msg;

    // 1, 2, 3 입력 대기
    while (true) {
        char key = _getch();
        if (key == '1') {
            return 1;
        }
        else if (key == '2') {
            return 2;
        }
        else if (key == '3') {
            return 3;
        }
    }
}