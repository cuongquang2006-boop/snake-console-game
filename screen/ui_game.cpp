#include "ui_game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;

char mainMenu()
{
    char choice;
    cout << " *----------------MENU---------------*" << endl;
    cout << "|| 1. START GAME                     ||" << endl;
    cout << "|| 2. CHOOSE DIFFICULTY              ||" << endl;
    cout << "|| 3. SNAKE SKIN                     ||" << endl;
    cout << "|| 4. CHOOSE MAP                     ||" << endl;
    cout << "|| 5. PLAYER LIST                    ||" << endl;
    cout << "|| 6. LEADERBOARD                    ||" << endl;
    cout << "|| 7. EXIT                           ||" << endl;
    cout << "||-----------------------------------*" << endl;
    cout << "|| Enter your choice (1/2/3/4/5/6): ";
    cin >> choice;
    cout << "||===================================*" << endl;
    return choice;
}

char choiceMap()
{
    char choice;
    cout << " *--------------SELECT MAP--------------*" << endl;
    cout << "|| 1. Classic                           ||" << endl;
    cout << "|| 2. TwoLine                           ||" << endl;
    cout << "|| 3. TheThief                          ||" << endl;
    cout << " *--------------------------------------*" << endl;
    cout << "Choose a map (1/2/3): " << endl;
    cin >> choice;
    return choice;
}

void difficultyUI()
{
    cout << " *-------------SELECT DIFFICULTY-------------*" << endl;
    cout << "|| 1. EASY                                  ||" << endl;
    cout << "|| 2. MEDIUM                                ||" << endl;
    cout << "|| 3. HARD                                  ||" << endl;
    cout << " *-------------------------------------------*" << endl;
}

int chooseDifficulty()
{
    difficultyUI();
    char n;
    cin >> n;

    if (n == '1') return 70;
    if (n == '2') return 60;
    if (n == '3') return 40;

    return 70;
}

void skinChoice()
{
    cout << " *--------------SELECT COLOR---------------*" << endl;
    cout << "||            1.Default                    ||" << endl;
    cout << "||            2.Pink                       ||" << endl;
    cout << "||            3.Red                        ||" << endl;
    cout << "||            4.LBlue                      ||" << endl;
    cout << "||            5.Green                      ||" << endl;
    cout << "||            6.Yellow                     ||" << endl;
    cout << "||            7.Aqua                       ||" << endl;
    cout << "||            8.Purple                     ||" << endl;
    cout << "||            9.Blue                       ||" << endl;
    cout << " *-----------------------------------------*" << endl;
}

int chooseSkinColor()
{
    skinChoice();
    char s;
    cin >> s;

    if (s == '1') return 7;
    if (s == '2') return 13;
    if (s == '3') return 12;
    if (s == '4') return 9;
    if (s == '5') return 10;
    if (s == '6') return 14;
    if (s == '7') return 3;
    if (s == '8') return 5;
    if (s == '9') return 1;

    return 7;
}

int menuArrow(const vector<string>& items, const string& title)
{
    int n = items.size();
    int choice = 0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (true)
    {
        system("cls");

        if (!title.empty())
            cout << title << "\n";

        for (int i = 0; i < n; i++)
        {
            if (i == choice)
                SetConsoleTextAttribute(hConsole, 10);
            else
                SetConsoleTextAttribute(hConsole, 7);

            cout << "  " << items[i] << endl;
        }

        SetConsoleTextAttribute(hConsole, 7);

        int c = _getch();

        if (c == 224)
        {
            c = _getch();

            if (c == 72) choice--;
            if (c == 80) choice++;
        }
        else
        {
            if (c == 'w' || c == 'W') choice--;
            if (c == 's' || c == 'S') choice++;
        }

        if (c == 13)
            return choice;

        if (choice < 0) choice = n - 1;
        if (choice >= n) choice = 0;
    }
}

int chooseSkinColorArrowWrapper()
{
    vector<string> menu =
    {
        "1. Default",
        "2. Pink",
        "3. Red",
        "4. LBlue",
        "5. Green",
        "6. Yellow",
        "7. Aqua",
        "8. Purple",
        "9. Blue"
    };

    int idx = menuArrow(menu, "*--------------SELECT COLOR--------------*");

    int colors[] = { 7,13,12,9,10,14,3,5,1 };

    return colors[idx];
}

int chooseDifficultyArrowWrapper()
{
    vector<string> menu =
    {
        "1. EASY",
        "2. MEDIUM",
        "3. HARD"
    };

    int idx = menuArrow(menu, "*-------------SELECT DIFFICULTY-------------*");

    if (idx == 0) return 30;
    if (idx == 1) return 20;
    if (idx == 2) return 10;

    return 20;
}

char choiceMapArrowWrapper()
{
    vector<string> menu =
    {
        "1. Classic",
        "2. TwoLine",
        "3. HardX"
    };

    int idx = menuArrow(menu, "*--------------SELECT MAP--------------*");

    return '1' + idx;
}
