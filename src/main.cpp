#include "repl.hpp"
#include "board.hpp"
#include "move.hpp"
#include "zobrist.hpp"
#include <cstdio>
#include <ctime>
#include <string>

int main(int argc, char **argv) {
  //repl();

  int c = 1000;
  if (argc > 1) c = std::stoi(argv[1]);
  auto t = init_table();
  srand(std::time({}));
  for (int i = 0; i < c; i++) {
    auto b = random_board();
    auto h = hash(b, t);
  }
  
  /* int i = 5;
  if (argc > 1) i = std::stoi(argv[1]);
  board_t b = random_board();
  table_t t = init_table();
  BaseMove base{b, t, random_board(), i};
  printf("%lu\n", base.previous_hashes->size()); */  
  return 0;
}
