#include "game.h"
#include "food.h"
#include "snake.h"
#include "ui_game.h"

#include <iostream> 
#include <fstream> 
#include <sstream>
#include <vector>
#include <string>     
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib") 
using namespace std;

void musicTheme()
{
    PlaySound(TEXT("Pixel-adventures.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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
