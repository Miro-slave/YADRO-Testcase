#pragma once

#include "services/command_parser.h"
#include "services/lexeme_parser.h"
#include "entities/table.h"
#include "entities/club.h"

#include <ctime>
#include <unordered_set>
#include <queue>
#include <map>
#include <fstream>

namespace task {

class Application {
 public:
  static Application& getImplementation();

  void run(int argc, char* argv[]);

 private:
  Application() = default;
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

 private:
  std::ifstream input_file_stream_;

  enum {FILE_NAME_POS = 1};

  LexemeParser  lexeme_parser_;
  CommandParser command_parser_;

  Club club_;
}; 

}  // namespace task