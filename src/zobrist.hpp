#ifndef ZOBRIST_HPP_
#define ZOBRIST_HPP_

#include "board.hpp"
#include "util.hpp"

table_t init_table();
hashsize_t hash(board_t board, table_t table);

#endif
