// this file is provided.  do not modify. do not submit.
#include <iostream>
#include <vector>
#include "helper.h"
#include "logic.h"

using std::cout, std::endl;

// do not change
void PrintInstructions() {
  cout << endl
       << "---------------------------------------------------------" << endl
       << "Good day, adventurer!"                                     << endl
       << "Your goal is to get the treasure and escape the dungeon!"  << endl
       << " --- SYMBOLS ---"                                          << endl
       << " o          : That is you, the adventurer!"                << endl
       << " $          : These are treasures. Lots of money!"         << endl
       << " @          : These magical amulets resize the level."     << endl
       << " M          : These are monsters; avoid them!"             << endl
       << " +, -, |    : These are unpassable obstacles."             << endl
       << " ?          : A door to another level."                    << endl
       << " !          : A door to escape the dungeon."               << endl
       << " --- CONTROLS ---"                                         << endl
       << " w, a, s, d : Move up, left, down, and right."             << endl
       << " e          : Stay still for a turn."                      << endl
       << " q          : Abandon your quest."                         << endl
       << "---------------------------------------------------------" << endl
       << endl;
}

// do not change
void OutputMap(const std::vector<std::vector<char>>& map, const int max_row, const int max_col) {
  // output top border
  cout << "+";
  for (int i = 0; i < max_col * DISPLAY_WIDTH; ++i) {
    cout << "-";
  }
  cout << "+" << endl;

  for (int i = 0; i < max_row; ++i) {
    // output left border
    cout << "|";

    // output inner blocks
    for (int j = 0; j < max_col; ++j) {
      // output current block
      cout << " ";
      if (map.at(i).at(j) == TILE_OPEN) {
        cout << " ";
      } else {
        cout << map.at(i).at(j);
      }
      cout << " ";
    }

    // output right border
    cout << "|"  << endl;
  }

  // output bottom border
  cout << "+";
  for (int i = 0; i < max_col * DISPLAY_WIDTH; ++i) {
    cout << "-";
  }
  cout << "+" << endl;
}

// do not change
void OutputStatus(const int status, const Player& player, int moves) {
  if (status != STATUS_STAY) {
    cout << "You have moved to row " << player.row
         << " and column " << player.col << endl;
  }
  switch (status) {
    case STATUS_STAY:
      cout << "You stayed at row " << player.row
           << " and column " << player.col << endl
           << "You didn't move. Are you lost?" << endl;
      break;
    case STATUS_MOVE:
      break;
    case STATUS_TREASURE:
      cout << "Well done, adventurer! You found some treasure." << endl
           << "You now have " << player.treasure << " treasure"
           << (player.treasure == 1 ? "" : "s") << '.' << endl;
      break;
    case STATUS_AMULET:
      cout << "The magic amulet sparkles and crumbles into dust." << endl
           << "The ground begins to rumble. Are the walls moving?" << endl;
      break;
    case STATUS_LEAVE:
      cout << "You go through the doorway into the unknown beyond..." << endl;
      break;
    case STATUS_ESCAPE:
      cout << "Congratulations, adventurer!"
           << " You have escaped the dungeon!" << endl
           << "You escaped with " << player.treasure << " treasure"
           << (player.treasure == 1 ? " " : "s ")
           << "and in " << moves << " total moves." << endl;
      break;
  }
  cout << endl;
}

bool InvalidInput(char input) {
  return
    input != MOVE_UP &&
    input != MOVE_LEFT &&
    input != MOVE_DOWN &&
    input != MOVE_RIGHT &&
    input != INPUT_STAY;
}
