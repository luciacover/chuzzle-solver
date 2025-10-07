#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <cstdint>
#include <array>

typedef uint16_t u16;
typedef uint32_t u32;
typedef u32 hashsize_t;

constexpr u16 PIECES          = 8;
constexpr u16 BOARD_LENGTH    = 6;
constexpr u16 BOARD_SIZE      = BOARD_LENGTH * BOARD_LENGTH;
constexpr hashsize_t MAX_HASH = UINT32_MAX;

typedef std::array<std::array<hashsize_t, PIECES>, BOARD_SIZE> table_t;

#endif
