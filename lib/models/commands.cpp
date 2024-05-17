#pragma once

#include "commands.h"
#include "../enums/lexeme_type.h"

#include <iostream>
#include <sstream>
#include <iomanip>

namespace task {

void SetTableCountCommand::act(const std::vector<std::string>& lexemes,
                                     Club& club)  
{
  size_t table_count = std::stoull(lexemes[TABLE_COUNT_POS]);
  club.tables_.resize(table_count);
};

bool SetTableCountCommand::validate(const std::vector<std::string>& lexemes)  {
  if (lexemes.size() != std::size(lexeme_order_)) return false;

  return ICommand::validateBase(lexemes, lexeme_order_);
};



void SetWorkingTimeCommand::act(const std::vector<std::string>& lexemes,
                              Club& club) 
{
  std::cout << lexemes[BEGIN_TIME_POS] << '\n';

  club.begin_time_.tm_hour = std::stoi(lexemes[BEGIN_TIME_POS].substr(0, 2));
  club.begin_time_.tm_min = std::stoi(lexemes[BEGIN_TIME_POS].substr(3, 2));
  club.end_time_.tm_hour = std::stoi(lexemes[END_TIME_POS].substr(0, 2));
  club.end_time_.tm_min = std::stoi(lexemes[END_TIME_POS].substr(3, 2));
};

bool SetWorkingTimeCommand::validate(
    const std::vector<std::string>& lexemes)
{
  if (lexemes.size() != std::size(lexeme_order_)) return false;

  return ICommand::validateBase(lexemes, lexeme_order_);
};



void SetPriceForHourCommand::act(const std::vector<std::string>& lexemes,
                                 Club& club) 
{
  club.price_per_hour_ = std::stod(lexemes[HOUR_PRICE_POS]);
};

bool SetPriceForHourCommand::validate(const std::vector<std::string>& lexemes) {
  if (lexemes.size() != std::size(lexeme_order_)) return false;

  return ICommand::validateBase(lexemes, lexeme_order_);
};



void ClientHasArrivedCommand::act(const std::vector<std::string>& lexemes,
                                  Club& club) 
{
  printLexemes(lexemes);

  std::tm arrive_time{};
  arrive_time.tm_hour = std::stoi(lexemes[CLIENT_ARRIVE_TIME_POS].substr(0, 2));
  arrive_time.tm_min = std::stoi(lexemes[CLIENT_ARRIVE_TIME_POS].substr(3, 2));

  if (club.all_clients_.find(lexemes[CLIENT_NAME_POS]) !=
      club.all_clients_.end()) {
    std::cout << lexemes[CLIENT_ARRIVE_TIME_POS] << ' ' << ERR_CODE << ' '
              << "YouShallNotPass\n";
  } else if (!club.isOpen(arrive_time)) {
    std::cout << lexemes[CLIENT_ARRIVE_TIME_POS] << ' ' << ERR_CODE << ' '
              << "NotOpenYet\n";
  } else {
    club.all_clients_.insert(lexemes[CLIENT_NAME_POS]);
  }
};

bool ClientHasArrivedCommand::validate(
    const std::vector<std::string>& lexemes) {
  if (lexemes.size() != std::size(lexeme_order_)) return false;

  return ICommand::validateBase(lexemes, lexeme_order_);
};



void ClientTookATableCommand::act(const std::vector<std::string>& lexemes,
                                  Club& club) 
{
  printLexemes(lexemes);

  if (club.all_clients_.find(lexemes[CLIENT_NAME_POS]) ==
      club.all_clients_.end()) {
    std::cout << lexemes[CLIENT_ARRIVE_TIME_POS] << ' ' << ERR_CODE << ' '
              << "ClientUnkown\n";
    return;
  }

  size_t table_idx = std::stoull(lexemes[TABLE_NUMBER_POS]) - 1;

  if (club.tables_[table_idx].isTaken()) {
    std::cout << lexemes[CLIENT_ARRIVE_TIME_POS] << ' ' << ERR_CODE << ' '
              << "PlaceIsBusy\n";
    return;
  }

  std::tm take_time{};
  take_time.tm_hour = std::stoi(lexemes[CLIENT_ARRIVE_TIME_POS].substr(0, 2));
  take_time.tm_min = std::stoi(lexemes[CLIENT_ARRIVE_TIME_POS].substr(3, 2));

  club.tables_[table_idx].take(take_time);
  club.tables_index_by_client_.insert(
      std::make_pair(lexemes[CLIENT_NAME_POS], table_idx));
};

bool ClientTookATableCommand::validate(
    const std::vector<std::string>& lexemes) {
  if (lexemes.size() != std::size(lexeme_order_)) return false;

  return ICommand::validateBase(lexemes, lexeme_order_);
};


void ClientQuitCommand::act(const std::vector<std::string>& lexemes,
                            Club& club) 
{
  printLexemes(lexemes);

  std::tm quit_time{};
  quit_time.tm_hour = std::stoi(lexemes[CLIENT_ARRIVE_TIME_POS].substr(0, 2));
  quit_time.tm_min = std::stoi(lexemes[CLIENT_ARRIVE_TIME_POS].substr(3, 2));

  if (club.all_clients_.find(lexemes[CLIENT_NAME_POS]) ==
      club.all_clients_.end()) {
    std::cout << lexemes[CLIENT_ARRIVE_TIME_POS] << ' ' << ERR_CODE << ' '
              << "ClientUnkown\n";
  } else {
    club.all_clients_.erase(lexemes[CLIENT_NAME_POS]);
    auto clients_table_iter =
        club.tables_index_by_client_.find(lexemes[CLIENT_NAME_POS]);

    if (clients_table_iter != club.tables_index_by_client_.end()) {
      size_t client_table_idx = clients_table_iter->second;
      club.tables_[client_table_idx].free(quit_time);

      if (!club.client_queue_.empty()) {
        ClientTookATableCommand took_a_table_command;
        std::string next_client_name = club.client_queue_.front();
        club.client_queue_.pop();

        std::vector<std::string> new_command_lexemes = {
            lexemes[CLIENT_ARRIVE_TIME_POS],
            std::to_string(TAKE_A_TABLE_COMMAND_CODE), next_client_name,
            std::to_string(client_table_idx + 1)};

        took_a_table_command.act(new_command_lexemes, club);
      }
    }
  }
};

bool ClientQuitCommand::validate(const std::vector<std::string>& lexemes) {
  if (lexemes.size() != std::size(lexeme_order_)) return false;

  return ICommand::validateBase(lexemes, lexeme_order_);
};


void ClientIsWaitingCommand::act(const std::vector<std::string>& lexemes,
                                 Club& club) 
{
  printLexemes(lexemes);

  if (club.all_clients_.find(lexemes[CLIENT_NAME_POS]) ==
      club.all_clients_.end()) {
    std::cout << lexemes[CLIENT_ARRIVE_TIME_POS] << ' ' << ERR_CODE << ' '
              << "ClientUnkown\n";
  } else if (club.tables_index_by_client_.size() != club.tables_.size()) {
    std::cout << lexemes[CLIENT_ARRIVE_TIME_POS] << ' ' << ERR_CODE << ' '
              << "ICanWaitNoLonger!\n";
  } else if (club.client_queue_.size() > club.tables_.size()) {
    ClientQuitCommand client_quit_command;
    std::vector<std::string> new_command_lexemes = {
        lexemes[CLIENT_ARRIVE_TIME_POS], std::to_string(LEAVE_COMMAND_ID),
        lexemes[CLIENT_NAME_POS]};

    client_quit_command.act(new_command_lexemes, club);
  } else {
    club.client_queue_.push(lexemes[CLIENT_NAME_POS]);
  }
};

bool ClientIsWaitingCommand::validate(const std::vector<std::string>& lexemes) {
  if (lexemes.size() != std::size(lexeme_order_)) return false;

  return ICommand::validateBase(lexemes, lexeme_order_);
};


void ClubIsClosedCommand::act(const std::vector<std::string>& lexemes,
                              Club& club) 
{
  std::stringstream leaving_time;
  leaving_time << std::setw(2) << std::setfill('0') << club.end_time_.tm_hour
               << ':' << std::setw(2) << std::setfill('0')
               << club.end_time_.tm_min;

  std::vector<std::string> client_quit_command_lexemes = {
      leaving_time.str(), std::to_string(LEAVE_COMMAND_ID), "CLIENT-NAME"};

  for (const auto& client : club.all_clients_) {
    client_quit_command_lexemes[CLIENT_NAME_POS] = client;
    printLexemes(client_quit_command_lexemes);
  }

  std::cout << leaving_time.str() << '\n';

  for (size_t i = 0; i < club.tables_.size(); i++) {
    if (club.tables_[i].isTaken()) {
      club.tables_[i].free(club.end_time_);
    }

    std::stringstream total_working_time;
    total_working_time << std::setw(2) << std::setfill('0')
                       << club.tables_[i].timeWorked().tm_hour << ':'
                       << std::setw(2) << std::setfill('0')
                       << club.tables_[i].timeWorked().tm_min;

    std::cout << i + 1 << ' '
              << club.tables_[i].hoursWorked() * club.price_per_hour_ << ' '
              << total_working_time.str() << '\n';
  }
};

bool ClubIsClosedCommand::validate(const std::vector<std::string>& lexemes) {
  return lexemes.size() == 0;
};

}  // namespace task