#pragma once

#include "table.h"

#include <stdexcept>
#include <string>

namespace task {

void Table::free(const std::tm& time) {
  is_taken_ = false;

  int minute_diff = time.tm_min - last_taking_time_.tm_min;
  if (minute_diff < 0) {
    time_worked_.tm_min += 60 + minute_diff;
    time_worked_.tm_hour += time.tm_hour - last_taking_time_.tm_hour - 1;
  } else if (minute_diff == 0) {
    time_worked_.tm_hour += time.tm_hour - last_taking_time_.tm_hour;
  } else {
    time_worked_.tm_min += minute_diff;
    time_worked_.tm_hour += time.tm_hour - last_taking_time_.tm_hour;
  }

  time_worked_.tm_hour += time_worked_.tm_min / 60;
  time_worked_.tm_min %= 60;
}

void Table::take(const std::tm& taking_time) {
  if (isTaken()) {
    throw std::runtime_error("table has been taken already");
  }

  is_taken_ = true;
  last_taking_time_ = taking_time;
}

bool Table::isTaken() { return is_taken_; }

size_t Table::hoursWorked() {
  return time_worked_.tm_hour + time_worked_.tm_min != 0 ? 1 : 0;
}

std::tm Table::timeWorked() { return time_worked_; }

}  // namespace task