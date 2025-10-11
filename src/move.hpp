#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "board.hpp"
#include "zobrist.hpp"
#include <queue>
#include <memory>
#include <unordered_set>

typedef std::unordered_set<hashsize_t> prevhashes_t;

class Move {
public:
  Move(const table_t &table, const board_t &board,
       std::shared_ptr<std::unordered_set<hashsize_t>> previously_generated,
       const hashsize_t &goal, const int depth, std::queue<mod_t> prev_mods, bool &complete);
  ~Move() {}
};

class BaseMove : public Move {
private:
  const table_t table;
  bool complete = false;
  BaseMove(const board_t &board, const table_t &table, const hashsize_t &goal,
           const int depth, std::shared_ptr<prevhashes_t> h)
      : board(board), table(table), goal(goal), previous_hashes(h),
        Move(table, board, h, goal, depth, {}, this->complete) {}

public:
  std::shared_ptr<std::unordered_set<hashsize_t>> previous_hashes;
  const board_t board;
  const hashsize_t goal;
  BaseMove(const board_t &board, const table_t &table, const board_t &goal,
           const int &depth)
      : BaseMove(board, table, hash(goal, table), depth, std::make_shared<prevhashes_t>()) {}
};
#endif
