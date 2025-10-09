#include "zobrist.hpp"
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <unordered_map>

table_t init_table() {
  table_t table;

  for (auto &t : table) {
    for (auto &r : t) {
      r = std::rand() % MAX_HASH;
    }
  }

  return table;
}
