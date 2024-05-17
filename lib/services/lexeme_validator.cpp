#include "lexeme_validator.h"

#include <regex>
#include <stdexcept>

namespace task {

bool LexemeValidator::validate(const std::string& lexeme, ELexemeType lexeme_type) {
  std::regex expression;

  switch (lexeme_type) {
    case ELexemeType::CLIENT_NAME:
    case ELexemeType::ERROR_WORD:
      expression = "([0-9a-zA-Z]|_|-)+";
      break;
    case ELexemeType::TIMESTAMP:
      expression = "([0-1][0-9]|2[0-3]):[0-5][0-9]";
      break;
    case ELexemeType::EVENT_ID:
    case ELexemeType::NUMBER:
      expression = "[0-9]+";
      break;
    default:
      throw std::runtime_error("unknown lexeme type");
  }

  return std::regex_match(lexeme, expression);
}

}  // namespace task
