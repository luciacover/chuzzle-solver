#include "test.hpp"
#include "board.hpp"
#include "zobrist.hpp"
#include <unordered_set>
#include <cstdio>
#include <string>
#include <vector>

void zobrist_test() {
  const testfn_t generate_hash = []() {
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

void slide_test() {
  const auto row_mv = [](const std::string &init, const std::string &expected,
                         const int &row, const int &count) -> testfn_t {
    return [=]() {
      board_t board = string_to_board(init);
      const board_t expected_board = string_to_board(expected);

      slide_left(board, row, count);

      return (board == expected_board) ? 1 : 0;
    };
  };

  const testfn_t row0 = row_mv("RBYOCG WWWWWW WWWWWW WWWWWW WWWWWW WWWWWW", "OCGRBY WWWWWW WWWWWW WWWWWW WWWWWW WWWWWW", 0, 3);
  const testfn_t row1 = row_mv("WWWWWW RBYOCG WWWWWW WWWWWW WWWWWW WWWWWW", "WWWWWW CGRBYO WWWWWW WWWWWW WWWWWW WWWWWW", 1, 4);
  const testfn_t row2 = row_mv("WWWWWW WWWWWW RBYOCG WWWWWW WWWWWW WWWWWW", "WWWWWW WWWWWW GRBYOC WWWWWW WWWWWW WWWWWW", 2, 5);
  const testfn_t row3 = row_mv("WWWWWW WWWWWW WWWWWW RBYOCG WWWWWW WWWWWW", "WWWWWW WWWWWW WWWWWW BYOCGR WWWWWW WWWWWW", 3, 1);
  const testfn_t row4 = row_mv("WWWWWW WWWWWW WWWWWW WWWWWW RBYOCG WWWWWW", "WWWWWW WWWWWW WWWWWW WWWWWW YOCGRB WWWWWW", 4, 2);
  const testfn_t row5 = row_mv("WWWWWW WWWWWW WWWWWW WWWWWW WWWWWW RBYOCG", "WWWWWW WWWWWW WWWWWW WWWWWW WWWWWW OCGRBY", 5, 3);
  
  std::vector<testfn_t> slide_fns = { row0, row1, row2, row3, row4, row5 }; 
  MultiTest slide("Sliding", slide_fns);
  slide.run();
  printf("%s\n", slide.results().c_str());
}
