#include "board.hpp"
#include <algorithm>
#include <cstdio>
#include <unordered_map>

// converts a board to a string of chuzzles R/B/C/G/O/M/W/Y
std::string board_to_string(const board_t &board) {
  std::string out = "";

  for (const auto &c : board) {
    out += static_cast<char>(c);
  }

  return out;
}

// converts a string of chuzzles R/B/C/G/O/M/W/Y to a board
board_t string_to_board(const std::string &bs) {
  board_t board;
  std::ranges::transform(
      bs.begin(), bs.end(), board.begin(),
      [](const char &c) -> Chuzzle { return static_cast<Chuzzle>(c); });

  return board;
}

board_t random_board() {
  board_t board;

  constexpr std::array<Chuzzle, PIECES> chuzzles = {
      Chuzzle::RED,   Chuzzle::BLUE,   Chuzzle::CYAN,    Chuzzle::GREEN,
      Chuzzle::WHITE, Chuzzle::YELLOW, Chuzzle::RAINBOW, Chuzzle::ORANGE};
  std::ranges::generate_n(board.begin(), BOARD_SIZE, [chuzzles]() {
    return chuzzles.at(rand() % PIECES);
  });

  return board;
}

// calculates the 1d coordinate for the board given a 2d coord
constexpr int board_coord(const int &row, const int &col) {
  return row * BOARD_LENGTH + col;
}

void print_board(const board_t &board) {
  const std::unordered_map<Chuzzle, std::string> colors = {
      {Chuzzle::RED, "\e[31m"},       {Chuzzle::BLUE, "\e[34m"},
      {Chuzzle::CYAN, "\e[36m"},      {Chuzzle::GREEN, "\e[32m"},
      {Chuzzle::WHITE, "\e[37m"},     {Chuzzle::YELLOW, "\e[33m"},
      {Chuzzle::RAINBOW, "\e[1;35m"}, {Chuzzle::ORANGE, "\e[91m"}};

  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_LENGTH; j++) {
      printf("%sO\e[0m ", colors.at(board[board_coord(i, j)]).c_str());
    }

    printf("\n");
  }
}

// this definitely isnt optimal, i reckon i could probably do this inplace with
// std::swap, but bah humbug
board_t rotate_board(const board_t &board, const bool &left_rotate) {
  board_t dst;

  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_LENGTH; j++) {
      dst[board_coord(i, j)] =
          board[board_coord((left_rotate) ? j : BOARD_LENGTH - j - 1,
                            (left_rotate) ? BOARD_LENGTH - i - 1 : i)];
    }
  }

  return dst;
}

// !! DOESN'T DO BOUNDS CHECKS! THOSE SHOULD BE HANDLED ELSEWHERE!
void slide_left(board_t &board, const int &row, const int &count) {
  const int start_index = row * BOARD_LENGTH;
  std::rotate(board.begin() + start_index, board.begin() + start_index + count,
              board.begin() + start_index + BOARD_LENGTH);
}

void slide_down(board_t &board, const int &col, const int &count) {
  board_t board_cols = rotate_board(board, false);
  const int start_index = col * BOARD_LENGTH;

  std::rotate(board_cols.begin() + start_index,
              board_cols.begin() + start_index + count,
              board_cols.begin() + start_index + BOARD_LENGTH);

  board = std::move(rotate_board(board_cols, true));
}

board_t modify_board(const board_t &board, const mod_t &mod) {
  board_t b = board;

  const auto [dir, pos, count] = mod;
  if (pos > 5 || count > 5)
    return board;

  if (dir == 'l') {
    slide_left(b, pos, count);
  } else if (dir == 'd') {
    slide_down(b, pos, count);
  }

  return b;
}
