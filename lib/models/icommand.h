#pragma once

#include "../enums/lexeme_type.h"
#include "../enums/command_type.h"
#include "../entities/club.h"


#include <vector>
#include <string>
#include <vector>

namespace task {

class ICommand {
 public:
  virtual void act(const std::vector<std::string>& lexemes, Club& club) = 0;
  virtual bool validate(const std::vector<std::string>& lexemes) = 0;

protected:
  void printLexemes(const std::vector<std::string>& lexemes);

  bool validateBase(const std::vector<std::string>& lexemes, const ELexemeType lexemes_order[]);
};

}  // namespace task