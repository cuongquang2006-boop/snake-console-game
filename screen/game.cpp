#include "game.h"

void Game::musicTheme()
{
    PlaySound(TEXT("Pixel-adventures.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
void Game::musicOver()
{
    PlaySound(TEXT("Over.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void Game::musicEat()
{
    PlaySound(TEXT("Eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void gotoXY(int x, int y)
{
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void Game::chooseMap(char choose)
{
    if (choose == '1')
    {
        hangcot.clear();
    }
    else if (choose == '2')
    {
        hangcot.clear();
        for (int i = 6; i <= 30; i++)
        {
            hangcot.push_back({ 5,i });
        }
        for (int i = 6; i <= 30; i++)
        {
            hangcot.push_back({ 14,i });
        }
    }
    else if (choose == '3')
    {
        hangcot.clear();
        int r, m, n, c;
        r = 3;
        for (int i = 3; i < 16; i++)
        {
            if (i == 3)
            {
                for (int j = 0; j <= 3; j++)
                {
                    hangcot.push_back({ i,j });
                }
            }
            for (int j = 3; j < 11; j++)
            {
                if (j == r)
                {
                    hangcot.push_back({ i,j });
                    r++;
                    break;
                }
            }
        }

        m = 26;
        for (int i = 11; i < 18; i++)
        {
            if (i == 17)
            {
                for (int j = 32; j <= 37; j++)
                {
                    hangcot.push_back({ i,j });
                }
            }
            for (int j = 26; j < 36; j++)
            {
                if (j == m)
                {
                    hangcot.push_back({ i,j });
                    m++;
                    break;
                }
            }
        }
    }
}

void Game::draw()
{
    gotoXY(0, 0);

    for (int i = 0; i < WIDTH + 2; ++i) std::cout << "#";
    std::cout << endl;

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (j == 0) std::cout << "#";

            bool printed = false;

            if (snake.body[0].first == i && snake.body[0].second == j)
            {
                SetConsoleTextAttribute(hConsole, color);
                std::cout << "0";
                printed = true;
            }

            for (int k = 1; k < snake.body.size() && !printed; ++k)
            {
                if (snake.body[k].first == i && snake.body[k].second == j)
                {
                    SetConsoleTextAttribute(hConsole, color);
                    std::cout << "o";
                    printed = true;
                }
            }

            if (!printed && food.x == i && food.y == j)
            {
                std::cout << "*";
                printed = true;
            }

            for (auto x : hangcot)
            {
                if (!printed && x.first == i && x.second == j)
                {
                    std::cout << "#";
                    printed = true;
                    break;
                }
            }

            if (!printed) std::cout << " ";

            SetConsoleTextAttribute(hConsole, 7);

            if (j == WIDTH - 1) std::cout << "#";
        }

        std::cout << std::endl;
    }

    for (int i = 0; i < WIDTH + 2; ++i) std::cout << "#";

    std::cout << "\nPress |X| to restart the game.";
    std::cout << "\nScore: " << score << std::endl;
}

void Game::initSnake()
{
    snake.body.clear();

    int startX = 2;
    int startY = 13;
    int length = 3;

    snake.dir = RIGHT;

    for (int i = 0; i < length; ++i)
        snake.body.push_back({ startX, startY - i });
}

void Game::input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a': if (snake.dir != RIGHT) snake.dir = LEFT;  break;
        case 'd': if (snake.dir != LEFT)  snake.dir = RIGHT; break;
        case 'w': if (snake.dir != DOWN)  snake.dir = UP;    break;
        case 's': if (snake.dir != UP)    snake.dir = DOWN;  break;

        case 'x':
        {
            returnToMenu = true;
            gameOver = true;
            musicTheme();
            break;
            system("cls");
        }
        }
    }
}

void Game::logic()
{
    snake.move();

    if (snake.isCollision())
    {
        musicOver();
        Sleep(30);
        gameOver = true;
        isMusicPlaying = true;
        system("cls");
        return;
    }

    for (auto x : hangcot)
    {
        if (snake.body[0] == x)
        {
            musicOver();
            Sleep(30);
            gameOver = true;
            isMusicPlaying = true;
            system("cls");
            return;
        }
    }

    if (snake.body[0].first == food.x && snake.body[0].second == food.y)
    {
        musicEat();
        Sleep(25);
        score += 10;
        snake.grow();
        food.spawn(snake, hangcot);
        isMusicPlaying = true;
    }

    if (isMusicPlaying == false)
    {
        musicTheme();
        isMusicPlaying = true;
    }
}

void Game::setN(int n)
{
    this->n = n;
}

void Game::setColor(int color)
{
    this->color = color;
}

void Game::setName(string name)
{
    this->playername = name;
}

string Game::getName()
{
    return playername;
}

void Game::setDiachi(string dchi)
{
    this->diachi = dchi;
}

string Game::getDiachi()
{
    return diachi;
}

void Game::setScore(int score)
{
    this->score = score;
}

int Game::getScore()
{
    return score;
}

void Game::in()
{
    std::cout << "-----------------------------------------\n";
    std::cout << "Player: " << getName() << std::endl;
    std::cout << "Region: " << getDiachi() << std::endl;
    std::cout << "Score : " << getScore() << std::endl;
    std::cout << "-----------------------------------------\n";
}

void Game::run()
{
    while (!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(n);
    }

    system("cls");

    std::cout << "GAME OVER!" << std::endl;
}