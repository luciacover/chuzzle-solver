#include "repl.hpp"
#include "board.hpp"
#include "zobrist.hpp"

#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cctype>
#include <cstdio>
#include <regex>

void set_raw(termios &original) {
  termios raw = original;
  raw.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void restore_term(const termios &original) {
  tcsetattr(STDIN_FILENO, TCSANOW, &original);
}

bool allowed(char c) {
  return std::isalnum(c) || c == ' ' || c == '+' || c == ',';
}

std::string read_input() {
  std::string input;
  char c;
  while (1) {
    c = getchar();

    if (c == '\n' || c == '\r') {
      std::cout << std::endl;
      break;
    } else if (c == 127 || c == 8) { // backspace i think im too tired to make this comment bro
      if (!input.empty()) {
        input.pop_back();
        std::cout << "\b \b";
      }
    } else if (allowed(c)) {
      input.push_back(c);
      putchar(c);
      fflush(stdout);
    }
  }

  return input;
}

void repl() {
  // setting up the terminal
  termios original;
  tcgetattr(STDIN_FILENO, &original);
  set_raw(original);
  
  printf("CHUZZLE SOLVER REPL\n");
  printf("type ,h for help.\n");

  bool board_initialized = false;
  table_t table = init_table();
  board_t board;
  while (1) {
    printf("> ");

    std::string in = read_input();
    // checking single-character commands
    if (in == "q") {
      printf("goodbye, friend :(");
      break;
    } else if (in == "h") {
      if (!board_initialized) {
        printf("[ERROR]: board uninitialized. create board before generating hash.\n");
        continue;
      }

      printf("%xd\n", hash(board, table));
      continue;
    } else if (in == "t") {
      table = init_table();

      for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < PIECES; j++) {
          printf("%x ", table[i][j]);
        }

        printf("\n");
      }
      continue;
    } else if (in == "p") {
      if (!board_initialized) {
        printf("[ERROR]: board uninitialized. create board before printing.\n");
        continue;
      }

      print_board(board);
      continue;
    } else if (in == "r") {
      board_initialized = true;
      board = random_board();

      print_board(board);
      continue;
    } else if (in == ",h") {
      printf("b <board string> - creates a new board with a given board string.\n");
      printf("r                - sets the board to be a randomly generated one.\n");
      printf("p                - prints the board\n");
      printf("l<row>+<count>   - moves the row to the left by count. row and count are between 0 - 5 inclusive.\n");
      printf("d<col>+<count>   - similar to moving left, but down instead.\n");
      printf("t                - recreates the hashing table.\n");
      printf("h                - hashes the board\n");
      printf(",h               - this help message :D!!!\n");
      printf("q                - quits the program... but you wouldn't do that right? :>\n");
    }

    std::regex board_pattern(R"(b ([RBCGOMWY]{36}))");
    std::regex left_pattern(R"(l([012345])\+([012345]))");
    std::regex down_pattern(R"(d([012345])\+([012345]))");
    std::smatch matches;
    if (std::regex_match(in, matches, board_pattern)) {
      std::string b = matches[1];

      board_initialized = true;
      board = string_to_board(b);
      print_board(board);
      continue;
    } else if (std::regex_match(in, matches, left_pattern)) {
      if (!board_initialized) {
        printf("[ERROR]: board uninitialized. create board to shift.\n");
        continue;
      }

      int row = stoi(matches[1]);
      int count = stoi(matches[2]);

      slide_left(board, row, count);
      print_board(board);
      continue;
    } else if (std::regex_match(in, matches, down_pattern)) {
      if (!board_initialized) {
        printf("[ERROR]: board uninitialized. create board to shift.\n");
        continue;
      }

      int col = stoi(matches[1]);
      int count = stoi(matches[2]);

      slide_down(board, col, count);
      print_board(board);
      continue;
    }
  }

  restore_term(original);
}
