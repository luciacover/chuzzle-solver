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

  // this and the function above could (and probably should) be combined into a single one at some point.
  const auto col_mv = [](const std::string &init, const std::string &expected,
                         const int &col, const int &count) -> testfn_t {
      return [=]() {
        board_t board = string_to_board(init);
        const board_t expected_board = string_to_board(expected);

        slide_up(board, col, count);

        return (board == expected_board) ? 1 : 0;
      };
    };

  std::vector<testfn_t> slide_fns = {
      row_mv("RBYOCG WWWWWW WWWWWW WWWWWW WWWWWW WWWWWW",
             "RBYOCG WWWWWW WWWWWW WWWWWW WWWWWW WWWWWW", 0, 0),
      row_mv("WWWWWW RBYOCG WWWWWW WWWWWW WWWWWW WWWWWW",
             "WWWWWW BYOCGR WWWWWW WWWWWW WWWWWW WWWWWW", 1, 1),
      row_mv("WWWWWW WWWWWW RBYOCG WWWWWW WWWWWW WWWWWW",
             "WWWWWW WWWWWW YOCGRB WWWWWW WWWWWW WWWWWW", 2, 2),
      row_mv("WWWWWW WWWWWW WWWWWW RBYOCG WWWWWW WWWWWW",
             "WWWWWW WWWWWW WWWWWW OCGRBY WWWWWW WWWWWW", 3, 3),
      row_mv("WWWWWW WWWWWW WWWWWW WWWWWW RBYOCG WWWWWW",
             "WWWWWW WWWWWW WWWWWW WWWWWW CGRBYO WWWWWW", 4, 4),
      row_mv("WWWWWW WWWWWW WWWWWW WWWWWW WWWWWW RBYOCG",
             "WWWWWW WWWWWW WWWWWW WWWWWW WWWWWW GRBYOC", 5, 5),
      col_mv("RWWWWW BWWWWW YWWWWW OWWWWW CWWWWW GWWWWW",
             "RWWWWW BWWWWW YWWWWW OWWWWW CWWWWW GWWWWW", 0, 0),
      col_mv("WRWWWW WBWWWW WYWWWW WOWWWW WCWWWW WGWWWW",
             "WBWWWW WYWWWW WOWWWW WCWWWW WGWWWW WRWWWW", 1, 1),
    };

  MultiTest slide("Sliding", slide_fns);
  slide.run();
  printf("%s\n", slide.results().c_str());
}
