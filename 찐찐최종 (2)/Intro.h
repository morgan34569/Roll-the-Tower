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
