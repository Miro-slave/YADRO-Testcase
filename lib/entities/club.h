#pragma once

#include "table.h"

#include <ctime>
#include <unordered_set>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <vector>


namespace task {

struct Club {
  std::tm begin_time_;
  std::tm end_time_;

  double  price_per_hour_;

  std::set<std::string> all_clients_;
  std::vector<Table>              tables_;
  std::map<std::string, size_t>   tables_index_by_client_;
  std::queue<std::string>         client_queue_;

  bool isOpen(const std::tm& time);
};

}  // namespace task