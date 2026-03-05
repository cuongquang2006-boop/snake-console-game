#pragma once
#include "snake.h"
#include "food.h"
#include <windows.h> 
#include <conio.h> 
#include <vector>
#include <ctime>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")  
#include <thread>
#include <chrono>

using namespace std;
void gotoXY(int x, int y);
void hideCursor();

class Game
{
public:
    vector<pair<int, int>> hangcot;
    Snake snake;
    Food food;
    string playername;
    string diachi;
    int n;
    int color;
    int score;
    bool isMusicPlaying = false;
    bool gameOver;
    Game() : snake(3, 10)
    {
        gotoXY(0, 0);
        srand(time(0));
        food.spawn(snake, hangcot);
        score = 0;
        gameOver = false;
    }
    void musicTheme();
    void musicOver();
    void musicEat();
    void chooseMap(char choose);
    void draw();
    bool returnToMenu = false;
    void initSnake();
    void input();
    void logic();
    void setN(int n);
    void setColor(int color);
    void setName(string name);
    string getName();
    void setDiachi(string dchi);
    string getDiachi();
    void setScore(int score);
    int getScore();
    void in();
    void run();
};
