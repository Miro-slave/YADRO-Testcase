#pragma once

#include "../enums/command_type.h"
#include "../models/icommand.h"
#include "lexeme_validator.h"

#include <memory>
#include <string>
#include <vector>

namespace task {

class CommandParser {
 public:
  std::unique_ptr<ICommand> parse(const std::vector<std::string>& lexemes);

 private:
  enum { EVENT_ID_POS = 1 };

  static constexpr ECommandType commands_order_[4] = {
      ECommandType::SET_TABLE_COUNT, ECommandType::SET_WORKING_TIME,
      ECommandType::SET_PRICE_FOR_HOUR, ECommandType::COMMAND_BY_ID};

  size_t line_counter_ = 0;

  LexemeValidator lexeme_validator_;
};

}  // namespace task