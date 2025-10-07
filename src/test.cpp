#include "test.hpp"
#include "board.hpp"
#include "zobrist.hpp"
#include <unordered_set>
#include <cstdio>
#include <string>

void zobrist_test() {
  testfn_t generate_hash = []() {
    table_t table = init_table();
    std::unordered_set<hashsize_t> hashes;
    std::unordered_set<std::string> previously_generated;

    for (int i = 0; i < BOARD_SIZE * PIECES; i++) {
      const board_t board = random_board();
      const hashsize_t board_hash = hash(board, table);
      const std::string board_str = board_to_string(board);

      const bool generated = previously_generated.contains(board_str);
      const bool collision = hashes.contains(board_hash);

      if (generated) {
        continue;
      }

      if (collision) {
        return 0;
      } else {
        hashes.insert(board_hash);
      }

      previously_generated.insert(board_str);
    }

    return 1;
  };
  
  RepeatTest zobrist("Zobrist Hashing", 100, generate_hash);
  zobrist.run();
  printf("%s\n", zobrist.results().c_str());
}
