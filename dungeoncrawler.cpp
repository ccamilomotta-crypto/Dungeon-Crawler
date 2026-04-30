// this file is provided.  do not modify. do not submit.
#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "logic.h"

using std::cin, std::cout, std::endl, std::string, std::vector;

int main() {
  // display greeting message
  PrintInstructions();

  string dungeon;
  int total_rooms;

  Player player;

  cout << "Please enter the dungeon name and number of levels: ";
  cin >> dungeon >> total_rooms;

  int total_moves = 0;
  for (int current_room = 1; current_room <= total_rooms; current_room++) {
    cout << "Level " << current_room << endl;
    string file_name = dungeon + std::to_string(current_room) + ".txt";

    // declare variables
    int max_row = 0;
    int max_col = 0;
    int next_row = 0;
    int next_col = 0;

    // create map, or quit if map load error
    vector<vector<char>> map = LoadLevel(file_name, max_row, max_col, player);
    if (map.empty()) {
      cout << "Returning you back to the real word, adventurer!" << endl;
      return 1;
    }

    // display map
    OutputMap(map, max_row, max_col);

    // move player
    char input = 0;
    int status = 0;
    while (true) {
      // get user input
      cout << "Enter command (w,a,s,d: move, e: stay still, q: quit): ";
      cin >> input;

      // quit game if user inputs quit
      if (input == INPUT_QUIT) {
        cout << "Thank you for playing!" << endl;
        return 0;
      }

      // reprompt if invalid command
      if (InvalidInput(input)) {
        cout << "I did not understand your command, adventurer!" << endl;
        continue;
      }

      // increment dungeon movement counter
      total_moves++;
      if (input == INPUT_STAY) {
        status = STATUS_STAY;
      } else {
        // translate from the character input to a direction
        // we will use the player's current location and pass-by-reference
        // to find the intended next location
        next_row = player.row;
        next_col = player.col;
        GetDirection(input, next_row, next_col);

        // move player to new location index, if possible, and get player status
        status = DoPlayerMove(map, max_row, max_col, player, next_row, next_col);
      }

      // quit game if user escapes
      if (status == STATUS_ESCAPE) {
        OutputMap(map, max_row, max_col);
        OutputStatus(status, player, total_moves);
        return 0;
      }

      // go to next level if user goes through door
      if (status == STATUS_LEAVE) {
        OutputMap(map, max_row, max_col);
        OutputStatus(status, player, total_moves);
        break;
      }

      // move monsters, end if player is caught
      if (DoMonsterAttack(map, max_row, max_col, player)) {
        OutputMap(map, max_row, max_col);
        cout << "You died, adventurer! Better luck next time!" << endl;
        return 0;
      }

      // use amulet
      if (status == STATUS_AMULET) {
        ResizeMap(map, max_row, max_col);
      }

      // display map and status
      OutputMap(map, max_row, max_col);
      OutputStatus(status, player, total_moves);
    }
  }
  return 0;
}
