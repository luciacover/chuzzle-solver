#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "board.hpp"
#include "zobrist.hpp"
#include <memory>
#include <optional>
#include <tuple>
#include <unordered_set>
#include <vector>

typedef std::unordered_set<hashsize_t> prevhashes_t;

class Move {
public:
  const hashsize_t move_hash;
  const std::optional<std::tuple<char, u8, u8>> modification;
  std::vector<std::shared_ptr<Move>> next_moves;
  Move(const table_t &table, const board_t &initial,
       const hashsize_t &board_hash,
       const std::optional<std::tuple<char, u8, u8>> &mod,
       std::shared_ptr<std::unordered_set<hashsize_t>> previously_generated,
       const board_t &goal);
  ~Move() {}
};

class BaseMove : public Move {
private:
  const table_t table;
  BaseMove(const board_t &board, const table_t &table, const board_t &goal,
           std::shared_ptr<prevhashes_t> h)
      : board(board), table(table), goal(goal), previous_hashes(h),
        Move(table, board, hash(board, table), std::nullopt, h, goal) {}

public:
  std::shared_ptr<std::unordered_set<hashsize_t>> previous_hashes;
  const board_t board;
  const board_t goal;
  BaseMove(const board_t &board, const table_t &table, const board_t &goal)
      : BaseMove(board, table, goal, std::make_shared<prevhashes_t>()) {}
};
#endif
