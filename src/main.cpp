#include "zobrist.hpp"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <string>

board_t random_board() {
  board_t board;

  constexpr std::array<Chuzzle, PIECES> chuzzles = { Chuzzle::RED, Chuzzle::BLUE, Chuzzle::CYAN,
                                            Chuzzle::GREEN, Chuzzle::WHITE, Chuzzle::YELLOW,
                                            Chuzzle::RAINBOW, Chuzzle::ORANGE };
  for (auto &c : board) {
    c = static_cast<Chuzzle>(chuzzles[rand() % PIECES]);
  }

  return board;
}


// hash boards and check for collisions
// the checks for previously generated board significantly slows down
// the tests, *but* prevent false collisions by making sure we dont generate
// the same board twice. this could be resolved by taking the cartesian product
// of all chuzzles rather than randomly generating boards.
int run_tests(table_t table) {
  std::unordered_set<hashsize_t> hashes;
  std::unordered_set<std::string> previously_generated;
  int failures = 0;

  for (int i = 0; i < BOARD_SIZE * PIECES; i++) {
    board_t board = random_board();
    hashsize_t board_hash = hash(board, table);
    std::string board_str = board_to_string(board);

    bool generated = previously_generated.contains(board_str);
    bool collision = hashes.contains(board_hash);

    if (generated) {
      continue;
    } else if (collision) {
      failures++;
    } else {
      hashes.insert(board_hash);
    }

    previously_generated.insert(board_str);
  }

  return failures;
}

int main(void) {
  std::srand(std::time({}));

  const int tests = 1000000;
  int failed = 0;
  
  for (int i = 0; i < tests; i++) {
    auto table = init_table();
    int res = run_tests(table);

    if (res) {
      printf("TEST %d: \e[31m[%d COLLISION(S)]\e[0m\n", i + 1, res);
      failed++;
    }
  }

  printf("%d/%d passed!\n", tests - failed, tests);
  printf("%.5f%% failed\n", (failed / (double)tests) * 100);
}
