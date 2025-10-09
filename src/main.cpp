#include "repl.hpp"
#include "board.hpp"
#include "move.hpp"
#include "zobrist.hpp"
#include <cstdio>

int main(void) {
//  repl();
  board_t b = random_board();
  table_t t = init_table();
  BaseMove base{b, t, random_board(), 9};
  printf("-------\n");
  Move m{t, b, std::tuple('l', 0, 5), base.previous_hashes, random_board(), 9};
  return 0;
}
