#include "move.hpp"
#include "board.hpp"
#include <cstdio>
#include "zobrist.hpp"

int main(void) {
  board_t b = random_board();
  table_t t = init_table();
  BaseMove move(b, t, b);

  for (auto i : *move.previous_hashes) {
    printf("%d\n", i);
  }

  for (auto i : move.next_moves) {
    printf("%d\n", (*i).move_hash); 
  }
  
  return 0;
}
