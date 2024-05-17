#include "icommand.h"
#include "../services/lexeme_validator.h"

#include <iostream>

namespace task {

bool ICommand::validateBase(
  const std::vector<std::string>& lexemes, 
  const ELexemeType lexemes_order[]) 
{
  LexemeValidator lexeme_validator;
  for (size_t i = 0; i < lexemes.size(); i++) {
    if (!lexeme_validator.validate(lexemes[i], lexemes_order[i])) {
      return false;
    }
  }

  return true;
}

void ICommand::printLexemes(const std::vector<std::string>& lexemes) {
  std::for_each(lexemes.begin(), lexemes.end(),
                [](const std::string& lexeme) { std::cout << lexeme << ' '; });
  std::cout << '\n';
}

}  // namespace task