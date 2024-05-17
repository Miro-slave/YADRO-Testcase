#include "lexeme_parser.h"

#include <iterator>
#include <sstream>
#include <stdexcept>

namespace task {


std::vector<std::string> LexemeParser::parse(const std::string& line) {
  std::istringstream iss(line);

  return {std::istream_iterator<std::string>(iss),
          std::istream_iterator<std::string>()};
}

};  // namespace task