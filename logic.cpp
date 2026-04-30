#include <string>
#include <vector>
#include "logic.h"
#include "player.h"

using std::string, std::vector;

vector<vector<char>> LoadLevel(const string& file_name, int& max_row, int& max_col, Player& player) {
  // TODO(student): implement this function
  ifstream fin(file_name);
  if(!fin.is_open()){
    return {};}
  int rows =0;
  int cols =0;
  int start_row=0;
  int start_col =0;

  if(!(fin>>rows>> cols>> start_row>>start_col)){
    return {};}
  if(rows<= 0 ||cols <=0){
    return {};
  }

  long long total_tiles =1LL *rows*cols;
  if(total_tiles>INT32_MAX){
    return {};}
  if(start_row <0||start_row>=rows ||start_col <0 ||start_col >=cols){
    return {};
  }
  vector<vector<char>> temp_map(rows, vector<char>(cols, TILE_OPEN));

  for(int r =0;r <rows;r++){
    for(int c =0;c <cols;c++){
      char tile =0;
      if(!(fin >> tile)){
        return {};
      }

      if(tile !=TILE_OPEN&&tile !=TILE_TREASURE &&tile !=TILE_AMULET &&tile !=TILE_MONSTER&&tile !=TILE_PILLAR && tile !=TILE_DOOR &&tile !=TILE_EXIT){
        return {};}
      temp_map[r][c] =tile;}}
  char extra =0;
  if(fin>>extra){
    return {};}
  if(temp_map[start_row][start_col]!=TILE_OPEN){
    return {};
  }
  temp_map[start_row][start_col] =TILE_PLAYER;
  max_row =rows;
  max_col =cols;
  player.row =start_row;
  player.col =start_col;
  return temp_map;
}
void GetDirection(char input, int& next_row, int& next_col) {
  // TODO(student): implement this function
  if(input ==MOVE_UP){
    next_row--;
  }else if(input ==MOVE_DOWN){
    next_row++;
  }else if(input ==MOVE_LEFT){
    next_col--;
  }else if(input ==MOVE_RIGHT){
    next_col++;
  }
}

void ResizeMap(vector<vector<char>>& map, int& max_row, int& max_col) {
  // TODO(student): implement this function
  if(max_row<=0||max_col <=0){
    return;
  }
  if(static_cast<int>(map.size()) !=max_row){
    return;
  }
  for(int r =0;r< max_row;r++){
    if(static_cast<int>(map[r].size())!=max_col){
      return;
    }}
  long long new_rows =2LL *max_row;
  long long new_cols =2LL *max_col;
  if (new_rows *new_cols >INT32_MAX){
    return;
  }
  vector<vector<char>> old_map =map;
  vector<vector<char>> new_map(static_cast<int>(new_rows),vector<char>(static_cast<int>(new_cols),TILE_OPEN));

  for(int r =0;r <max_row;r++){
    for(int c=0;c<max_col;c++){
      char tile =old_map[r][c];
      char copied_tile =tile;
      if (copied_tile ==TILE_PLAYER){
        copied_tile =TILE_OPEN;
      }
      new_map[r][c] =tile;
      new_map[r][c +max_col] =copied_tile;
      new_map[r +max_row][c] =copied_tile;
      new_map[r +max_row][c +max_col]=copied_tile;
    }}
  map =new_map;
  max_row *=2;
  max_col *=2;
}
int DoPlayerMove(vector<vector<char>>& map, int max_row, int max_col, Player& player, int next_row, int next_col) {
  // TODO(student): implement this function
  if(next_row <0|| next_row>=max_row ||next_col<0||next_col >=max_col){
    return STATUS_STAY;
  }
  char next_tile =map[next_row][next_col];
  if(next_tile ==TILE_PILLAR ||next_tile ==TILE_MONSTER){
    return STATUS_STAY;
  }
  if(next_tile ==TILE_EXIT &&player.treasure<1){
    return STATUS_STAY;
  }
  int status =STATUS_MOVE;
  if(next_tile ==TILE_TREASURE){
    player.treasure++;
    status =STATUS_TREASURE;
  }else if(next_tile==TILE_AMULET){
    status =STATUS_AMULET;
  }else if(next_tile ==TILE_DOOR){
    status =STATUS_LEAVE;
  }else if(next_tile ==TILE_EXIT){
    status=STATUS_ESCAPE;
  }
  map[player.row][player.col]=TILE_OPEN;
  player.row =next_row;
  player.col =next_col;
  map[player.row][player.col] =TILE_PLAYER;

  return status;
}
bool DoMonsterAttack(vector<vector<char>>& map, int max_row, int max_col, const Player& player) {
  // TODO(student): implement this function
  for(int r =player.row-1;r>=0;r--){
    if(map[r][player.col] ==TILE_PILLAR){
      break;
    }
    if(map[r][player.col] ==TILE_MONSTER){
      map[r][player.col] =TILE_OPEN;
      map[r +1][player.col] =TILE_MONSTER;
    }}
  for(int r=player.row +1; r<max_row;r++){
    if(map[r][player.col] ==TILE_PILLAR){
      break;
    }
    if(map[r][player.col] ==TILE_MONSTER){
      map[r][player.col] =TILE_OPEN;
      map[r-1][player.col] =TILE_MONSTER;
    }}

  for(int c =player.col-1;c>=0;c--){
    if(map[player.row][c]==TILE_PILLAR){
      break;
    }
    if(map[player.row][c]==TILE_MONSTER){
      map[player.row][c]=TILE_OPEN;
      map[player.row][c+1] =TILE_MONSTER;
    }}

  for(int c=player.col +1;c<max_col;c++){
    if(map[player.row][c] ==TILE_PILLAR){
      break;
    }
    if(map[player.row][c] ==TILE_MONSTER){
      map[player.row][c] =TILE_OPEN;
      map[player.row][c -1] =TILE_MONSTER;
    }}

  return map[player.row][player.col] ==TILE_MONSTER;
}

