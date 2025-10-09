#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "board.hpp"
#include <memory>
#include <optional>
#include <unordered_set>
#include <vector>

typedef std::unordered_set<hashsize_t> prevhashes_t;

class Move {
public:
  const std::optional<mod_t> mod;
  std::vector<std::shared_ptr<Move>> next_moves;
  Move(const table_t &table, const board_t &initial,
       const std::optional<mod_t> &modification,
       std::shared_ptr<std::unordered_set<hashsize_t>> previously_generated,
       const board_t &goal, const int depth);
  ~Move() {}
};

class BaseMove : public Move {
private:
  const table_t table;
  BaseMove(const board_t &board, const table_t &table, const board_t &goal,
           const int depth, std::shared_ptr<prevhashes_t> h)
      : board(board), table(table), goal(goal), previous_hashes(h),
        Move(table, board, std::nullopt, h, goal, depth) {}

public:
  std::shared_ptr<std::unordered_set<hashsize_t>> previous_hashes;
  const board_t board;
  const board_t goal;
  BaseMove(const board_t &board, const table_t &table, const board_t &goal,
           const int &depth)
      : BaseMove(board, table, goal, depth, std::make_shared<prevhashes_t>()) {}
};
#endif
