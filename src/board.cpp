#include "board.hpp"
#include <cstdio>
#include <unordered_map>
#include <algorithm>

std::string board_to_string(const board_t &board) {
  std::string out = "";

  for (const auto &c : board) {
    out += static_cast<char>(c);
  }

  return out;
}

board_t string_to_board(const std::string &bs) {
  board_t board;
  int pos = 0;

  for (char c : bs) {
    switch (c) {
      case 'R':
      case 'B':
      case 'C':
      case 'G':
      case 'O':
      case 'M':
      case 'W':
      case 'Y':
        board[pos++] = static_cast<Chuzzle>(c);
        break;
      default:
        break;
    }

    if (pos >= BOARD_SIZE) break;
  }

  return board;
}

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

void print_board(const board_t &board) {
  const std::unordered_map<Chuzzle, std::string> colors = { {Chuzzle::RED, "\e[31m"},
                                                            {Chuzzle::BLUE, "\e[34m"},
                                                            {Chuzzle::CYAN, "\e[36m"},
                                                            {Chuzzle::GREEN, "\e[32m"},
                                                            {Chuzzle::WHITE, "\e[37m"},
                                                            {Chuzzle::YELLOW, "\e[33m"},
                                                            {Chuzzle::RAINBOW, "\e[1;35m"},
                                                            {Chuzzle::ORANGE, "\e[91m"} };

  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_LENGTH; j++) {
      printf("%sO\e[0m ", colors.at(board[i * BOARD_LENGTH + j]).c_str());
    }

    printf("\n");
  }
}

// !! DOESN'T DO BOUNDS CHECKS! THOSE SHOULD BE HANDLED ELSEWHERE!
void slide_left(board_t &board, const int &row, const int &count) { 
  const int start_index = row * BOARD_LENGTH;
  std::rotate(board.begin() + start_index,
              board.begin() + start_index + count,
              board.begin() + start_index + BOARD_LENGTH);
}
