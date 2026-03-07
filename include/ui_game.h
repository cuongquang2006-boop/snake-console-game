#pragma once
#include <vector>
#include <string>

char mainMenu();
char choiceMap();

void difficultyUI();
int chooseDifficulty();

void skinChoice();
int chooseSkinColor();

int menuArrow(const std::vector<std::string>& items, const std::string& title = "");

int chooseSkinColorArrowWrapper();
int chooseDifficultyArrowWrapper();
char choiceMapArrowWrapper();