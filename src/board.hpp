#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "chuzzle.hpp"
#include "util.hpp"
#include <string>
#include <tuple>

typedef std::array<Chuzzle, BOARD_SIZE> board_t;
typedef std::tuple<char, u8, u8> mod_t;

std::string board_to_string(const board_t &board);
board_t string_to_board(const std::string &bs);
void print_board(const board_t &board);
void slide_left(board_t &board, const int &row, const int &count);
void slide_down(board_t &board, const int &col, const int &count);
board_t random_board();
board_t modify_board(const board_t &board, const mod_t &mod);

#endif
