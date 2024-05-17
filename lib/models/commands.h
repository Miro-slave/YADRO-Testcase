#pragma once

#include "icommand.h"
#include "../enums/lexeme_type.h"

#include <iostream>
#include <sstream>
#include <iomanip>

namespace task {

class SetTableCountCommand final : public ICommand {
 public:
  void act(const std::vector<std::string>& lexemes, Club& club) override;

  bool validate(const std::vector<std::string>& lexemes) override;

 private:
  enum {TABLE_COUNT_POS = 0};
  static constexpr ELexemeType lexeme_order_[1] = {ELexemeType::NUMBER};
};


class SetWorkingTimeCommand final : public ICommand {
 public:
  void act(const std::vector<std::string>& lexemes, Club& club) override;

  bool validate(const std::vector<std::string>& lexemes) override;

 private:
  enum {BEGIN_TIME_POS = 0, END_TIME_POS = 1};
  static constexpr ELexemeType lexeme_order_[2] = {ELexemeType::TIMESTAMP, ELexemeType::TIMESTAMP};
};


class SetPriceForHourCommand final : public ICommand {
 public:
  void act(const std::vector<std::string>& lexemes, Club& club) override;

  bool validate(const std::vector<std::string>& lexemes) override;

 private:
  enum { HOUR_PRICE_POS = 0 };
  static constexpr ELexemeType lexeme_order_[1] = {ELexemeType::NUMBER};
};


class ClientHasArrivedCommand final : public ICommand {
 public:
  void act(const std::vector<std::string>& lexemes, Club& club) override;

  bool validate(const std::vector<std::string>& lexemes) override;

 private:
  enum { CLIENT_ARRIVE_TIME_POS = 0, CLIENT_NAME_POS = 2, ERR_CODE = 13 };
  static constexpr ELexemeType lexeme_order_[3] = {
      ELexemeType::TIMESTAMP, ELexemeType::NUMBER, ELexemeType::CLIENT_NAME};
};


class ClientTookATableCommand final : public ICommand {
 public:
  void act(const std::vector<std::string>& lexemes, Club& club) override;

  bool validate(const std::vector<std::string>& lexemes) override;

 private:
  enum { CLIENT_ARRIVE_TIME_POS = 0, TABLE_NUMBER_POS = 3, CLIENT_NAME_POS = 2, ERR_CODE = 13 };
  static constexpr ELexemeType lexeme_order_[4] = {
       ELexemeType::TIMESTAMP, ELexemeType::NUMBER, ELexemeType::CLIENT_NAME,
       ELexemeType::NUMBER};
};


class ClientQuitCommand final : public ICommand {
 public:
  void act(const std::vector<std::string>& lexemes, Club& club) override;

  bool validate(const std::vector<std::string>& lexemes) override;

 private:
  enum {
    CLIENT_ARRIVE_TIME_POS = 0,
    TABLE_NUMBER_POS = 1,
    CLIENT_NAME_POS = 2,
    ERR_CODE = 13,
    TAKE_A_TABLE_COMMAND_CODE = 12
  };

  static constexpr ELexemeType lexeme_order_[3] = {
      ELexemeType::TIMESTAMP, ELexemeType::NUMBER, ELexemeType::CLIENT_NAME};
};


class ClientIsWaitingCommand final : public ICommand {
 public:
  void act(const std::vector<std::string>& lexemes, Club& club) override;

  bool validate(const std::vector<std::string>& lexemes) override;

 private:
  enum {
    CLIENT_ARRIVE_TIME_POS = 0,
    TABLE_NUMBER_POS = 1,
    CLIENT_NAME_POS = 2,
    LEAVE_COMMAND_ID = 11,
    ERR_CODE = 13
  };

  static constexpr ELexemeType lexeme_order_[3] = {
      ELexemeType::TIMESTAMP, ELexemeType::NUMBER, ELexemeType::CLIENT_NAME};
};


class ClubIsClosedCommand final : public ICommand {
 public:
  void act(const std::vector<std::string>& lexemes, Club& club) override;

  bool validate(const std::vector<std::string>& lexemes) override;

private:
  enum {
    CLIENT_ARRIVE_TIME_POS = 0,
    TABLE_NUMBER_POS = 1,
    CLIENT_NAME_POS = 2,
    LEAVE_COMMAND_ID = 11,
    ERR_CODE = 13
  };
};

}  // namespace task