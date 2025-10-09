#ifndef ZOBRIST_HPP_
#define ZOBRIST_HPP_

#include "board.hpp"
#include "util.hpp"
#include <unordered_map>

table_t init_table();
constexpr hashsize_t hash(const board_t &board, const table_t &table) {
  hashsize_t hash = 0;

  const std::unordered_map<Chuzzle, int> chuzzle_values = {
      {Chuzzle::RED, 0},   {Chuzzle::BLUE, 1},   {Chuzzle::CYAN, 2},
      {Chuzzle::GREEN, 3}, {Chuzzle::ORANGE, 4}, {Chuzzle::RAINBOW, 5},
      {Chuzzle::WHITE, 6}, {Chuzzle::YELLOW, 7}};
  for (std::size_t i = 0; i < BOARD_SIZE; i++) {
    const u8 j = chuzzle_values.at(board[i]);
    hash ^= table[i][j];
  }

  return hash;
}

//hashsize_t hash(const board_t &board, const table_t &table);

#endif
