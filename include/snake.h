#pragma once
#include <vector>
using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
const int WIDTH = 38;
const int HEIGHT = 20;

class Snake
{
public:
    vector<pair<int, int>> body;
    Direction dir;
    Snake(int startX, int startY, int length = 3)
    {
        dir = RIGHT;  
        for (int i = 0; i < length; ++i)
            body.push_back({ startX, startY - i });
    }
    void move()
    {
        for (int i = body.size() - 1; i > 0; --i)
            body[i] = body[i - 1];
        switch (dir)
        {
        case LEFT:  body[0].second--; break;
        case RIGHT: body[0].second++; break;
        case UP:    body[0].first--; break;
        case DOWN:  body[0].first++; break;
        default: break;
        }
    }
    void grow()
    {
        body.push_back(body.back());
    }
    bool isCollision()
    {
        if (body[0].first < 0 || body[0].first >= HEIGHT ||body[0].second < 0 || body[0].second >= WIDTH)
            return true;
        for (int i = 1; i < body.size(); ++i)
            if (body[0] == body[i]) return true;
        return false;
    }
};