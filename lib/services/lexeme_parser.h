#pragma once

#include "../enums/command_type.h"
#include "../models/icommand.h"
#include "lexeme_validator.h"

#include <memory>
#include <string>
#include <vector>


namespace task {

class LexemeParser {
 public:
  std::vector<std::string> parse(const std::string& line);
};

}  // namespace task