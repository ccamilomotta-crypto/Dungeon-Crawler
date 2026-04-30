// this file is provided.  do not modify. do not submit.
#ifndef PROVIDED_HELPER_H_
#define PROVIDED_HELPER_H_

#include <vector>
#include "player.h"

// constant value for tile width in console output
const int DISPLAY_WIDTH = 3;

// function signatures, do not change
void PrintInstructions();

void OutputMap(
    const std::vector<std::vector<char>>& map,
    const int max_row,
    const int max_col);

void OutputStatus(
    const int status,
    const Player& player,
    int moves);

bool InvalidInput(char input);

#endif  // PROVIDED_HELPER_H_
