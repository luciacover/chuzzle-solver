#include "zobrist.hpp"
#include <cstdlib>
#include <unordered_map>

table_t init_table() {
  table_t table;

  for (auto &t : table) {
    for (auto &r : t) {
      r = std::rand() % MAX_HASH;
    }
  }

  return table;
}

hashsize_t hash(board_t board, table_t table) {
  hashsize_t hash = 0;

  const std::unordered_map<Chuzzle, int> chuzzle_values = {
      {Chuzzle::RED, 0},   {Chuzzle::BLUE, 1},   {Chuzzle::CYAN, 2},
      {Chuzzle::GREEN, 3}, {Chuzzle::ORANGE, 4}, {Chuzzle::RAINBOW, 5},
      {Chuzzle::WHITE, 6}, {Chuzzle::YELLOW, 7}};
  for (int i = 0; i < BOARD_SIZE; i++) {
    int j = chuzzle_values.at(board[i]);
    hash ^= table[i][j];
  }

  return hash;
}
