#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <unordered_set>
#include <array>
#include <string>

#define BOARD_LENGTH 6
#define BOARD_SIZE   BOARD_LENGTH * BOARD_LENGTH
#define PIECES       8
#define MAX_HASH     UINT32_MAX

enum Chuzzle {
  RED = 0,
  BLUE,
  CYAN,
  GREEN,
  ORANGE,
  RAINBOW,
  WHITE,
  YELLOW,
};

typedef uint32_t hashsize_t;
typedef std::array<std::array<hashsize_t, PIECES>, BOARD_SIZE> table_t;
typedef std::array<Chuzzle, BOARD_SIZE> board_t;

// generating the initial table for zobrist hashing
table_t init_table() {
  table_t table;

  for (auto &t : table) {
    for (auto &r : t) {
      r = std::rand() % MAX_HASH;
    }
  }

  return table;
}

// calculates the zobrist hash for a given board
hashsize_t hash(board_t board, table_t table) {
  hashsize_t hash = 0;
  for (int i = 0; i < BOARD_SIZE; i++) {
    int j = board[i];
    hash ^= table[i][j];
  }

  return hash;
}

std::string board_string(board_t board) {
  std::string out = "";

  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_LENGTH; j++) {
      switch (board[i*BOARD_LENGTH + j]) {
        case RED:
          out += "R";
          break;
        case BLUE:
          out += "B";
          break;
        case CYAN:
          out += "C";
          break;
        case GREEN:
          out += "G";
          break;
        case ORANGE:
          out += "O";
          break;
        case RAINBOW:
          out += "M";
          break;
        case WHITE:
          out += "W";
          break;
        case YELLOW:
          out += "Y";
          break;
        default:
          break;
      }
    }

    out += "\n";
  }

  return out;
}

board_t board_from_string(std::string bs) {
  board_t board;
  int pos = 0;

  for (char c : bs) {
    switch (c) {
      case 'R':
        board[pos++] = RED;
        break;
      case 'B':
        board[pos++] = BLUE;
        break;
      case 'C':
        board[pos++] = CYAN;
        break;
      case 'G':
        board[pos++] = GREEN;
        break;
      case 'O':
        board[pos++] = ORANGE;
        break;
      case 'M':
        board[pos++] = RAINBOW;
        break;
      case 'W':
        board[pos++] = WHITE;
        break;
      case 'Y':
        board[pos++] = YELLOW;
        break;
      default:
        break;
    }
    // this shouldn't happen but better safe than sorry
    if (pos >= BOARD_SIZE) break;
  }

  return board;
}

board_t random_board() {
  board_t board;

  for (int i = 0; i < BOARD_SIZE; i++) {
    board[i] = static_cast<Chuzzle>(rand() % 8);
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
    std::string board_str = board_string(board);
    
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

int main(int argc, char **argv) {
  std::srand(std::time({}));

  const int tests = 10000;
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

  return 0;
}
