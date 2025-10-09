#include "move.hpp"
#include "zobrist.hpp"
#include <array>
#include <tuple>

constinit const std::size_t MODS_SIZE = 60;

// generates an array of tuples that represent all possible modifications that can be made to a given board.
[[nodiscard]]
consteval std::array<std::tuple<char, u8, u8>, MODS_SIZE> generate_mods() {
  std::array<std::tuple<char, u8, u8>, MODS_SIZE> out;

  for (std::size_t i{0}, pos{0}; pos <= 5; pos++) {
    for (std::size_t count{1}; count <= 5 && i < MODS_SIZE - 1; count++) {
      out.at(i++) = std::tuple('l', pos, count);
      out.at(i++) = std::tuple('d', pos, count);
    }
  }
  
  return out;
}

constinit const auto mods = generate_mods();

Move::Move(const table_t &table, const board_t &initial,
           const std::optional<std::tuple<char, u8, u8>> &modification,
           std::shared_ptr<std::unordered_set<hashsize_t>> previously_generated,
           const board_t &goal, const int depth)
    : mod(modification) {

  for (const auto &m : mods) {
    const auto [ dir, pos, count ] = m;
  
    // fucked up evil solution
    if (const auto [ b_dir, b_pos, _ ] = this->mod.value_or(std::tuple(' ', 255, 255)); b_dir == dir && b_pos == pos)
       continue;     

    printf("%c %d %d\n", dir, pos, count);
  }      
}
