#include "repl.hpp"
#include "board.hpp"
#include "move.hpp"
#include "zobrist.hpp"
#include <cstdio>

int main(void) {
  //repl();
  board_t b = random_board();
  table_t t = init_table();
  BaseMove base{b, t, random_board(), 1};
  for (auto h : *base.previous_hashes) {
    printf("%d\n", h);  
  }
  
  return 0;
}
