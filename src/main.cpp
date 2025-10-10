#include "repl.hpp"
#include "board.hpp"
#include "move.hpp"
#include "zobrist.hpp"
#include <cstdio>
#include <ctime>
#include <string>

int main(int argc, char **argv) {
  //repl();

  int i = 5;
  if (argc > 1) i = std::stoi(argv[1]);
  board_t b = string_to_board("RBRBRBGYGYGYOCOCOCRRBBBBOOOYGGBBBBBB");
  board_t g = string_to_board("OBRBRBBYGYGYRCOCOCGRBBBBOOOYGGRBBBBB");
  
  table_t t = init_table();
  BaseMove base{b, t, g, i};
  return 0;
}
