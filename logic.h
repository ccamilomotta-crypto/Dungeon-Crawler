// this file is provided.  do not modify. do not submit.
#ifndef PROVIDED_LOGIC_H_
#define PROVIDED_LOGIC_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "player.h"

using std::cin, std::cout, std::endl, std::string, std::ifstream, std::vector;

// constants for tile status
const char TILE_OPEN      = '-';  // blank
const char TILE_PLAYER    = 'o';  // player's current location
const char TILE_TREASURE  = '$';  // treasure location
const char TILE_AMULET    = '@';  // hazard that enlarges the dungeon
const char TILE_MONSTER   = 'M';  // monster current location
const char TILE_PILLAR    = '+';  // unpassable pillar location
const char TILE_DOOR      = '?';  // door to the next room
const char TILE_EXIT      = '!';  // exit door out of dungeon

// constants for movement status flags
const int STATUS_STAY     = 0;    // player has stayed still
const int STATUS_MOVE     = 1;    // player has moved in a direction
const int STATUS_TREASURE = 2;    // player has stepped onto the treasure
const int STATUS_AMULET   = 3;    // player has stepped onto an amulet
const int STATUS_LEAVE    = 4;    // player has left the current room
const int STATUS_ESCAPE   = 5;    // player has gone through the dungeon exit

// constants for user's keyboard inputs
const char INPUT_QUIT     = 'q';  // quit command
const char INPUT_STAY     = 'e';  // no movement
const char MOVE_UP        = 'w';  // up movement
const char MOVE_LEFT      = 'a';  // left movement
const char MOVE_DOWN      = 's';  // down movement
const char MOVE_RIGHT     = 'd';  // right movement

/**
 * Load representation of the dungeon level from file into the 2D map.
 * @param[in]  file_name File name of dungeon level.
 * @param[out] max_row   Number of rows in the dungeon table (aka height).
 * @param[out] max_col   Number of columns in the dungeon table (aka width).
 * @param[out] player    Player object by reference to set starting position.
 * @returns 2D vector representation of dungeon map with player's location, or an empty vector if loading fails for any reason
 * @update  max_row, max_col, player
 */
vector<vector<char>> LoadLevel(
  const std::string& file_name,
  int& max_row,
  int& max_col,
  Player& player);

/**
 * Translate the character direction input by the user into row or column change.
 * That is, updates `next_row` or `next_col` according to the player's movement direction.
 * @param[in]     input    Character input by the user which translates to a direction.
 * @param[in,out] next_row Player's next row on the dungeon map (up/down).
 * @param[in,out] next_col Player's next column on dungeon map (left/right).
 * @returns None
 */
void GetDirection(
  char input,
  int& next_row,
  int& next_col);

/**
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player.
 * @param[in,out] map     Dungeon map.
 * @param[in,out] max_row Number of rows in the dungeon table (aka height), to be doubled.
 * @param[in,out] max_col Number of columns in the dungeon table (aka width), to be doubled.
 * @returns None
 */
void ResizeMap(
  vector<vector<char>>& map,
  int& max_row,
  int& max_col);

/**
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure.
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param[in,out] map      Dungeon map.
 * @param[in]     max_row  Number of rows in the dungeon table (aka height).
 * @param[in]     max_col  Number of columns in the dungeon table (aka width).
 * @param[in,out] player   Player object to by reference to see current location.
 * @param[in]     next_row Player's next row on the dungeon map (up/down).
 * @param[in]     next_col Player's next column on dungeon map (left/right).
 * @returns Player's movement status after updating player's position.
 */
int DoPlayerMove(
  vector<vector<char>>& map,
  int max_row,
  int max_col,
  Player& player,
  int next_row,
  int next_col);

/**
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param[in,out] map     Dungeon map.
 * @param[in]     max_row Number of rows in the dungeon table (aka height).
 * @param[in]     max_col Number of columns in the dungeon table (aka width).
 * @param[in,out] player  Player object by reference for current location.
 * @returns true if monster reaches the player, false if not.
 */
bool DoMonsterAttack(
  vector<vector<char>>& map,
  int max_row,
  int max_col,
  const Player& player);

#endif  // PROVIDED_LOGIC_H_
