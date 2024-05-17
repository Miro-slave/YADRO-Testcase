#include "command_parser.h"
#include "../models/commands.h"

#include <iterator>
#include <sstream>
#include <stdexcept>

namespace task {

std::unique_ptr<ICommand> CommandParser::parse(const std::vector<std::string>& lexemes) {
  ECommandType command_type =
    commands_order_[std::min(line_counter_, std::size(commands_order_) - 1)];

  line_counter_++;

  if (command_type == ECommandType::COMMAND_BY_ID &&
    !lexeme_validator_.validate(lexemes[EVENT_ID_POS], ELexemeType::EVENT_ID)) 
  {
    throw std::runtime_error("invalid event id");
  }

  std::unique_ptr<ICommand> command = nullptr;
  switch (command_type) {
  case ECommandType::SET_TABLE_COUNT:
    command = std::make_unique<SetTableCountCommand>();   break;
  case ECommandType::SET_WORKING_TIME:
    command = std::make_unique<SetWorkingTimeCommand>();  break;
  case ECommandType::SET_PRICE_FOR_HOUR:
    command = std::make_unique<SetPriceForHourCommand>(); break;
  case ECommandType::COMMAND_BY_ID:

    switch (std::stoull(lexemes[EVENT_ID_POS])) {
    case 1:
      command = std::make_unique<ClientHasArrivedCommand>(); break;
    case 2:
      command = std::make_unique<ClientTookATableCommand>(); break;
    case 3:
      command = std::make_unique<ClientIsWaitingCommand>();  break;
    case 4:
      command = std::make_unique<ClientQuitCommand>();       break;
    default:
      throw std::runtime_error("unknown command by id type");
    }
    break;
  default:
    throw std::runtime_error("unknown command type");
  }

  if (!command.get()->validate(lexemes)) {
    throw std::runtime_error("invalid command");
  }

  return command;
}

};  // namespace task