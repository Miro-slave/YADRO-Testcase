#pragma once

#include "club.h"

namespace task {

bool Club::isOpen(const std::tm& time) {
    bool too_early = begin_time_.tm_hour > time.tm_hour || 
      (begin_time_.tm_hour == time.tm_hour && begin_time_.tm_min > begin_time_.tm_min);

    bool too_late = end_time_.tm_hour < time.tm_hour ||
      (end_time_.tm_hour == end_time_.tm_hour && end_time_.tm_min < end_time_.tm_min);

    return !(too_early || too_late);
  }

}  // namespace task