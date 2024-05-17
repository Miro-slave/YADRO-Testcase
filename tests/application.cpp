#include "../lib//application.h"

#include <gtest/gtest.h>

#include <sstream>

using namespace task;


TEST(LexemeValidatorUnvalidTimeSuit, EmptyTest) {
  LexemeValidator lexeme_validator;
  std::vector<std::string> invalid_lexemes = {"24:59", "16:71", "9:45", "  :12", "09:  ", "24:00"};
  ELexemeType lexeme_type = ELexemeType::TIMESTAMP;

  for (const auto& lexeme : invalid_lexemes) {
    ASSERT_FALSE(lexeme_validator.validate(lexeme, lexeme_type));
  }
}

TEST(LexemeValidatorValidTimeSuit, EmptyTest) {
  LexemeValidator lexeme_validator;
  std::vector<std::string> invalid_lexemes = {"23:59", "06:32", "00:00", "12:09",
                                              "09:09"};
  ELexemeType lexeme_type = ELexemeType::TIMESTAMP;

  for (const auto& lexeme : invalid_lexemes) {
    ASSERT_TRUE(lexeme_validator.validate(lexeme, lexeme_type));
  }
}

TEST(TableBeingUsedTwiceExceptionSuit, EmptyTest) {
  EXPECT_ANY_THROW({
    Table table;
    std::tm time{};
    table.take(time);
    table.take(time);
  });
}

TEST(InvalidArgumentsCountExceptionSuit, EmptyTest) {
  for (size_t i = 0; i < 5; i++) {
    if (i == 2) continue;

    EXPECT_ANY_THROW({
      char** empty_ptr = nullptr;
      Application::getImplementation().run(i, empty_ptr);
    });
  }
}

TEST(InvalidFileNameExceptionSuit, EmptyTest) {
  char** empty_ptr = new char*[2];
  empty_ptr[0] = "task.exe";
  empty_ptr[1] = "INVALID-FILE-PATH.invalid";

  EXPECT_ANY_THROW({
    Application::getImplementation().run(2, empty_ptr);
  });

  delete[] empty_ptr;
}

TEST(CommandParserInvalidTableCountSuit, EmptyTest) {
  CommandParser command_parser;
  std::vector<std::vector<std::string>> commands_lexemes = {
    {"One"}
  };

  size_t invalid_line_idx = commands_lexemes.size() - 1;

  EXPECT_ANY_THROW({
    command_parser.parse(commands_lexemes[invalid_line_idx]);
  });
}

TEST(CommandParserInvalidTimeLimitsSuit, EmptyTest) {
  CommandParser command_parser;
  std::vector<std::vector<std::string>> commands_lexemes = {
    {"1"},
    {"10:00", "24:59"}
  };

  for (size_t i = 0; i < commands_lexemes.size() - 1; i++) {
    command_parser.parse(commands_lexemes[i]);
  }

  size_t invalid_line_idx = commands_lexemes.size() - 1;

  EXPECT_ANY_THROW({
    command_parser.parse(commands_lexemes[invalid_line_idx]); 
  });
}

TEST(CommandParserInvalidHourPriceSuit, EmptyTest) {
  CommandParser command_parser;
  std::vector<std::vector<std::string>> commands_lexemes = {
    {"1"},
    {"10:00", "23:59"},
    {"-10"}
  };

  for (size_t i = 0; i < commands_lexemes.size() - 1; i++) {
    command_parser.parse(commands_lexemes[i]);
  }

  size_t invalid_line_idx = commands_lexemes.size() - 1;

  EXPECT_ANY_THROW({
    command_parser.parse(commands_lexemes[invalid_line_idx]); 
  });
}

TEST(CommandParserInvalidEventSuit, EmptyTest) {
  CommandParser command_parser;
  std::vector<std::vector<std::string>> commands_lexemes = {
    {"1"},
    {"10:00", "23:59"},
    {"10"},
    {"08:48", "1", "Client1", "THIS_COMMAND_IS_INVALID"}
  };

  for (size_t i = 0; i < commands_lexemes.size() - 1; i++) {
    command_parser.parse(commands_lexemes[i]);
  }

  size_t invalid_line_idx = commands_lexemes.size() - 1;

  EXPECT_ANY_THROW({
    command_parser.parse(commands_lexemes[invalid_line_idx]); 
  });
}

TEST(CommandParserValidSuit, EmptyTest) {
  CommandParser command_parser;
  std::vector<std::vector<std::string>> commands_lexemes = {
    {"1"},
    {"10:00", "23:59"},
    {"10"},
    {"08:48", "1", "Client1"},
    {"09:41", "1", "Client1"},
    {"09:48", "1", "Client2"},
  };

  EXPECT_NO_THROW({
    for (size_t i = 0; i < commands_lexemes.size(); i++) {
      command_parser.parse(commands_lexemes[i]);
    }
  });
}

TEST(LexemeParserSuit, EmptyTest) {
  std::string message = " one t2o 3ree Fou!\t FFFive _sIX--- \n sev\\en";
  std::vector<std::string> valid_lexemes = {
      "one", "t2o", "3ree", "Fou!", "FFFive", "_sIX---", "sev\\en"};

  LexemeParser lexeme_parser;

  EXPECT_EQ(lexeme_parser.parse(message), valid_lexemes);
}