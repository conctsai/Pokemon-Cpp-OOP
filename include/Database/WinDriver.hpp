#pragma once
#include "Database/Database.hpp"
#include <vector>

#define WINDRIVER WinDriver::getInstance()

struct WinInterface
{
    int user_id;
    int win;
    int total;
};

class WinDriver
{
private:
    WinDriver() = default;
    WinDriver(const WinDriver &) = delete;
    WinDriver(WinDriver &&) = delete;
    WinDriver &operator=(const WinDriver &) = delete;
    const char *table_name = "win";
    int col = 3;
    const std::string col_name[3] = {"user_id", "win", "total"};

public:
    std::vector<WinInterface> getAllWins() const noexcept;
    WinInterface getWinByUserId(int user_id) const;
    WinInterface insertWin(int user_id, int win, int total) const;
    bool updateWin(int user_id, int win, int total) const;
    ~WinDriver() = default;
    static const WinDriver &getInstance() noexcept;
};