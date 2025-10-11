#include "move.hpp"
#include "board.hpp"
#include "zobrist.hpp"
#include <array>
#include <barrier>
#include <mutex>
#include <thread>
#include <tuple>

constinit const std::size_t MODS_SIZE = 60;

std::mutex mtx;

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

Move::Move(const table_t &table, const board_t &board,
           std::shared_ptr<prevhashes_t> previously_generated,
           const hashsize_t &goal, const int depth, std::queue<mod_t> prev_mods,
           std::shared_ptr<bool> complete) {

  if (depth <= 0)
    return;

  std::barrier sync(8);
  std::queue<mod_t> path;
  const auto fn = [&](mod_t m) {
    //sync.arrive_and_wait();
    auto p = prev_mods;
    const board_t next_board = modify_board(board, m);
    const hashsize_t next_hash = hash(next_board, table);

    {
      std::lock_guard<std::mutex> guard(mtx);
      if (previously_generated->contains(next_hash))
        return;

      p.push(m);
    }

    if (next_hash == goal) {
      std::lock_guard<std::mutex> guard(mtx);
      path = p;
      *complete = true;
      return;
    }

    {
      std::lock_guard<std::mutex> guard(mtx);
      previously_generated->insert(next_hash);
    }
    Move move{table, next_board, previously_generated, goal, depth - 1,
              p,     complete};

  };

  std::vector<std::jthread> threads;
  for (const auto &m : mods) {
    if (*complete.get() == true) break;
    threads.emplace_back(fn, m);
  }

  if (path.empty())
    return;

  for (; !path.empty(); path.pop()) {
    auto [n, l, r] = path.front();
    printf("%c %d %d\n", n, l, r);
  }
  printf("-----\n");
}
