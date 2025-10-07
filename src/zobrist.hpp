#ifndef ZOBRIST_HPP_
#define ZOBRIST_HPP_

#include "util.hpp"
#include "board.hpp"

table_t init_table();
hashsize_t hash(board_t board, table_t table);

#endif
