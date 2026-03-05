#pragma once
#pragma once
#include "snake.h"
#include <iostream>
#include <vector>
class Food      
{
public:
    int x, y;
    void spawn(const Snake& snake, const vector<pair<int, int>>& walls)
    {
        while (true)
        {
            x = rand() % HEIGHT;
            y = rand() % WIDTH;
            bool conflict = false;
            for (auto seg : snake.body) 
            {
                if (seg.first == x && seg.second == y)
                {
                    conflict = true;
                    break;
                }
            }
            for (auto w : walls)
            {
                if (w.first == x && w.second == y)
                {
                    conflict = true;
                    break;
                }
            }
            if (!conflict) break;
        }
    }
};


