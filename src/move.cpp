#include "move.hpp"

Move::Move(const table_t &table, const board_t &initial,
           const hashsize_t &board_hash,
           const std::optional<std::tuple<char, u8, u8>> &mod,
           std::shared_ptr<std::unordered_set<hashsize_t>> previously_generated,
           const board_t &goal)
    : move_hash(board_hash), modification(mod) {
  previously_generated->insert(this->move_hash);

  if (this->modification)
    return;

  // simple test to make sure the shared ptr stuff works right
  for (int i = 0; i < 10; i++) {
    const board_t b = random_board();
    const hashsize_t h = hash(b, table);
    const auto t = std::make_tuple('c', 3, 4);
    const Move nm(table, initial, h, t, previously_generated, goal);
    const auto np = std::make_shared<Move>(nm);
    this->next_moves.push_back(np);
  }
}
