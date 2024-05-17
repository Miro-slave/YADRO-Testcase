#pragma once

#include <string>
#include <stdexcept>
#include <ctime>

namespace task {

class Table {
 public:

  void free(const std::tm& time);

  void take(const std::tm& taking_time);

  bool isTaken();

  size_t hoursWorked();

  std::tm timeWorked();

 private:
  bool is_taken_ = false;
  std::tm last_taking_time_{};
  std::tm time_worked_;
};



}  // namespace task