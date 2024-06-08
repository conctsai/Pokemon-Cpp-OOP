#pragma once

#include <vector>
#include <string>
#include <sqlite3.h>
#include <iostream>

#define DATABASE Database::getInstance()

class Database
{
private:
    sqlite3 *db;
    Database();
    Database(const Database &) = delete;
    Database(Database &&) = delete;
    Database &operator=(const Database &) = delete;
    const char *db_name = "game.db";

public:
    std::vector<std::string> queryAll(const std::string &) const;
    std::vector<std::string> queryByCondition(const std::string &, const std::string &) const;
    bool insert(const std::string &, const std::string &, const std::string &) const;
    bool deleteByCondition(const std::string &, const std::string &) const;
    bool updateByCondition(const std::string &, const std::string &, const std::string &) const;
    static const Database &getInstance();
    ~Database();
};