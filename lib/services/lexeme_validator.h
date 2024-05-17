#pragma once

#include "../enums/lexeme_type.h"

#include <string>

namespace task {

class LexemeValidator {
 public:
  bool validate(const std::string& lexeme, ELexemeType lexeme_type);
};  // class IValidator

}  // namespace task
