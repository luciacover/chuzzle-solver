#include "move.hpp"
#include "board.hpp"
#include "zobrist.hpp"
#include <array>
#include <tuple>

constinit const std::size_t MODS_SIZE = 60;

// generates an array of tuples that represent all possible modifications that
// can be made to a given board.
[[nodiscard]]
consteval std::array<mod_t, MODS_SIZE> generate_mods() {
  std::array<mod_t, MODS_SIZE> out;

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
           const std::optional<mod_t> &modification,
           std::shared_ptr<prevhashes_t> previously_generated,
           const board_t &goal, const int depth)
    : mod(modification) {

  if (depth <= 0)
    return;
  for (const auto &m : mods) {
    const auto [dir, pos, count] = m;

    // fucked up evil solution
    if (const auto [b_dir, b_pos, _] =
            this->mod.value_or(std::tuple(' ', 255, 255));
        b_dir == dir && b_pos == pos)
      continue;

    const board_t next_board = modify_board(initial, m);
    const hashsize_t next_hash = hash(next_board, table);

    if (previously_generated->contains(next_hash))
      continue;

    previously_generated->insert(next_hash);
    const auto next = std::make_shared<Move>(
        table, next_board, m, previously_generated, goal, depth - 1);
    this->next_moves.push_back(next);
  }
}
