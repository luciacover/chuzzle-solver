#ifndef CHUZZLE_HPP_
#define CHUZZLE_HPP_

#include "util.hpp"

enum class Chuzzle {
  RED     = 'R',
  BLUE    = 'B',
  CYAN    = 'C',
  GREEN   = 'G',
  ORANGE  = 'O',
  RAINBOW = 'M',
  WHITE   = 'W',
  YELLOW  = 'Y',
};

typedef std::array<Chuzzle, BOARD_SIZE> board_t;

#endif
