#include "game.h"
#include "food.h"
#include "snake.h"
#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string>     
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib") 
using namespace std;

int chooseSkinColorArrowWrapper();
int chooseDifficultyArrowWrapper();
char choiceMapArrowWrapper();

void musicTheme()
{
    PlaySound(TEXT("Pixel-adventures.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

char mainMenu()
{
    char choice;
    std::cout << " *----------------MENU---------------*" << std::endl;
    std::cout << "|| 1. START GAME                     ||" << std::endl;
    std::cout << "|| 2. CHOOSE DIFFICULTY              ||" << std::endl;
    std::cout << "|| 3. SNAKE SKIN                     ||" << std::endl;
    std::cout << "|| 4. CHOOSE MAP                     ||" << std::endl;
    std::cout << "|| 5. PLAYER LIST                    ||" << std::endl;
    std::cout << "|| 6. LEADERBOARD                    ||" << std::endl;
    std::cout << "|| 7. EXIT                           ||" << std::endl;
    std::cout << "||-----------------------------------*" << std::endl;
    std::cout << "|| Enter your choice (1/2/3/4/5/6): ";
    std::cin >> choice;
    std::cout << "||===================================*" << std::endl;
    return choice;
}

char choiceMap()
{
    char choice;
    std::cout << " *--------------SELECT MAP--------------*" << std::endl;
    std::cout << "|| 1. Classic                           ||" << std::endl;
    std::cout << "|| 2. TwoLine                           ||" << std::endl;
    std::cout << "|| 3. TheThief                          ||" << std::endl;
    std::cout << " *--------------------------------------*" << std::endl;
    std::cout << "Choose a map (1/2/3): " << std::endl;
    std::cin >> choice;
    return choice;
}

void difficultyUI()
{
    std::cout << " *-------------SELECT DIFFICULTY-------------*" << std::endl;
    std::cout << "|| 1. EASY                                  ||" << std::endl;
    std::cout << "|| 2. MEDIUM                                ||" << std::endl;
    std::cout << "|| 3. HARD                                  ||" << std::endl;
    std::cout << " *-------------------------------------------*" << std::endl;
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
    std::cout << " *--------------SELECT COLOR---------------*" << std::endl;
    std::cout << "||            1.Default                    ||" << std::endl;
    std::cout << "||            2.Pink                       ||" << std::endl;
    std::cout << "||            3.Red                        ||" << std::endl;
    std::cout << "||            4.LBlue                      ||" << std::endl;
    std::cout << "||            5.Green                      ||" << std::endl;
    std::cout << "||            6.Yellow                     ||" << std::endl;
    std::cout << "||            7.Aqua                       ||" << std::endl;
    std::cout << "||            8.Purple                     ||" << std::endl;
    std::cout << "||            9.Blue                       ||" << std::endl;
    std::cout << " *-----------------------------------------*" << std::endl;
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

const int MAX_CONTACTS = 1000;
Game contacts[MAX_CONTACTS];
int cnt = 0;
const string FILENAME = "Score.txt";

void taifile()
{
    ifstream file(FILENAME);
    if (!file)
    {
        ofstream file(FILENAME);
        file.close();
        return;
    }
    string line;
    cnt = 0;
    while (getline(file, line) && cnt < MAX_CONTACTS)
    {
        stringstream ss(line);
        string ten, diachi, diem;
        if (getline(ss, ten, ',') && getline(ss, diachi, ',') && getline(ss, diem))
        {
            contacts[cnt].setName(ten);
            contacts[cnt].setDiachi(diachi);
            contacts[cnt].setScore(stoi(diem));
            cnt++;
        }
    }
    file.close();
}

void luufile()
{
    ofstream file(FILENAME, ios::out);
    if (!file)
    {
        std::cout << "File does not exist!\n";
        return;
    }
    for (int i = 0; i < cnt; i++)
    {
        file << contacts[i].getName() << "," << contacts[i].getDiachi() << "," << contacts[i].getScore() << endl;
    }
    file.close();
}

void inds()
{
    if (cnt == 0)
    {
        std::cout << "The list is empty!\n";
        return;
    }
    for (int i = 0; i < cnt; i++)
    {
        std::cout << "Player information " << i + 1 << ":\n";
        contacts[i].in();
    }
}

// Bubble sort by score
void BubbleSort(vector<Game>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        bool check = false;
        for (int j = arr.size() - 1; j > i; j--)
        {
            if (arr[j].score > arr[j - 1].score)
            {
                Game temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                check = true;
            }
        }
        if (!check) break;
    }
}

HANDLE DUMA = GetStdHandle(STD_OUTPUT_HANDLE);

void bangXepHang(int top = 10)
{
    system("cls");
    if (cnt == 0)
    {
        std::cout << "No scores recorded yet!\n";
        return;
    }

    vector<Game> tmp(contacts, contacts + cnt);
    BubbleSort(tmp);

    SetConsoleTextAttribute(DUMA, 9);

    std::cout << "====================================================\n";
    std::cout << "||                   LEADERBOARD                 ||" << std::endl;
    std::cout << "||================================================||\n";
    std::cout << "||       NAME             ||   REGION   || SCORE ||" << std::endl;
    std::cout << "||========================||============||=======||\n";

    int n = min(top, cnt);

    for (int i = 0; i < n; i++)
    {
        std::cout << "||" << left << setw(23) << tmp[i].getName()
            << " || " << setw(10) << tmp[i].getDiachi()
            << " || " << right << setw(5) << tmp[i].getScore()
            << "  ||" << std::endl;
    }

    std::cout << "||========================||============||=======||\n";

    SetConsoleTextAttribute(DUMA, 7);
}

int main()
{
    musicTheme();
    hideCursor();
    taifile();

    while (true)
    {
        Game game;
        string name;
        int chondiachi;

        do
        {
            std::cout << "\nChoose region:\n1.SOUTH\n2.NORTH\n3.CENTRAL " << std::endl;

            std::cin >> chondiachi;
            std::cin.ignore(10000, '\n');

            std::cout << "Enter your name: ";
            getline(std::cin, name);

            game.setName(name);

            if (chondiachi > 3 || chondiachi < 1)
            {
                std::cout << "Invalid region! Please enter again!" << std::endl;
            }

            if (name.empty())
            {
                std::cout << "Name is empty! Please enter again!" << std::endl;
            }

            if (chondiachi == 1)  game.setDiachi("SOUTH");
            else if (chondiachi == 2)  game.setDiachi("NORTH");
            else if (chondiachi == 3)  game.setDiachi("CENTRAL");

            system("cls");

        } while (chondiachi > 3 || chondiachi < 1 || name.empty());

        char c = mainMenu();

        if (c == '5')
        {
            inds();
            break;
        }

        if (c == '6')
        {
            bangXepHang(10);
            system("pause");
        }

        if (c == '7')
        {
            std::cout << "You have exited the game!\n";
            break;
        }

        if (c == '1')
        {
            int m = chooseSkinColorArrowWrapper();
            system("cls");
            game.setColor(m);
            game.setN(30);
        }
        else if (c == '2')
        {
            int speed = chooseDifficultyArrowWrapper();
            system("cls");
            int m = chooseSkinColorArrowWrapper();
            system("cls");
            game.setColor(m);
            game.setN(speed);
        }
        else if (c == '3')
        {
            int m = chooseSkinColorArrowWrapper();
            system("cls");
            game.setColor(m);
            int speed = chooseDifficultyArrowWrapper();
            system("cls");
            game.setN(speed);
        }
        else if (c == '4')
        {
            char chonmap = choiceMapArrowWrapper();
            system("cls");
            int m = chooseSkinColorArrowWrapper();
            system("cls");
            game.setColor(m);
            int speed = chooseDifficultyArrowWrapper();
            system("cls");
            game.setN(speed);
            game.chooseMap(chonmap);
        }

        game.snake.dir = RIGHT;
        game.initSnake();
        game.food.spawn(game.snake, game.hangcot);
        game.run();

        if (!game.returnToMenu && game.getScore() > 0 || game.getScore() > 0)
        {
            contacts[cnt++] = game;
            luufile();
        }
    }
}

// arrow menu
int menuArrow(const vector<string>& items, const string& title = "")
{
    int n = items.size();
    int choice = 0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (true)
    {
        system("cls");

        if (!title.empty()) cout << title << "\n";

        for (int i = 0; i < n; i++)
        {
            if (i == choice) SetConsoleTextAttribute(hConsole, 10);
            else SetConsoleTextAttribute(hConsole, 7);

            cout << "  " << items[i] << endl;
        }

        SetConsoleTextAttribute(hConsole, 7);

        int c = _getch();

        if (c == 224)
        {
            c = _getch();

            if (c == 72)
            {
                choice--;
                Beep(800, 50);
            }

            if (c == 80)
            {
                choice++;
                Beep(800, 50);
            }
        }
        else
        {
            if (c == 'w' || c == 'W')
            {
                choice--;
                Beep(800, 50);
            }

            if (c == 's' || c == 'S')
            {
                choice++;
                Beep(800, 50);
            }
        }

        if (c == 13)
        {
            Beep(1000, 100);
            return choice;
        }

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

    if (idx == 1) return 30;
    if (idx == 2) return 20;
    if (idx == 3) return 10;

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