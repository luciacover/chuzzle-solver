#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "chuzzle.hpp"
#include "util.hpp"
#include <string>
#include <algorithm>
#include <tuple>

typedef std::array<Chuzzle, BOARD_SIZE> board_t;
typedef std::tuple<char, u8, u8> mod_t;

// these two could be constexpr but their performance isnt a bottleneck
std::string board_to_string(const board_t &board);
board_t string_to_board(const std::string &bs);

void print_board(const board_t &board);
void slide_left(board_t &board, const int &row, const int &count);
void slide_down(board_t &board, const int &col, const int &count);
board_t random_board();
board_t modify_board(const board_t &board, const mod_t &mod);
//std::string mod_to_string(); 

/* constexpr board_t string_to_board(const std::string &bs) {
  board_t board;
  std::ranges::transform(
      bs.begin(), bs.end(), board.begin(),
      [](const char &c) -> Chuzzle { return Chuzzle(c); });

  return board;
} */

#endif
