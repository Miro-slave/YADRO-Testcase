#include "application.h"
#include "models/commands.h"

#include <stdexcept>
#include <string>

namespace task {

void Application::run(int argc, char** argv) {
  if (argc != 2) throw std::runtime_error("invalid argument count");

  input_file_stream_.open(argv[FILE_NAME_POS]);

  if (!input_file_stream_.is_open()) {
    throw std::runtime_error("cannot open the file");
  }

  std::string line;
  while (!input_file_stream_.eof()) {
    std::getline(input_file_stream_, line, '\n');
    std::vector<std::string> lexemes = lexeme_parser_.parse(line);
    std::unique_ptr<ICommand> command = command_parser_.parse(lexemes);

    command.get()->act(lexemes, club_);
  }

  ClubIsClosedCommand club_is_closed_command;
  club_is_closed_command.act({}, club_);
}

Application& Application::getImplementation() {
  static Application impl;

  return impl;
}

}  // namespace task