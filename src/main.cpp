#include "board.hpp"

int main(void) {
  board_t board = string_to_board("RYRYRYGCGCGCBOBOBOMWMWMWRGRGRGBYBYBY");
  print_board(board);
  return 0;
}
