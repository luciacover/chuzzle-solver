#ifndef ZOBRIST_HPP_
#define ZOBRIST_HPP_

#include "util.hpp"
#include "chuzzle.hpp"
#include <string>

table_t init_table();
hashsize_t hash(board_t board, table_t table);
std::string board_to_string(board_t board);
board_t string_to_board(std::string bs);

#endif
