#include "Database/WinDriver.hpp"

std::vector<WinInterface> WinDriver::getAllWins() const noexcept
{
    std::vector<WinInterface> wins;
    std::vector<std::string> result = std::move(DATABASE.queryAll(this->table_name));
    for (int i = this->col; i < result.size(); i += this->col)
    {
        wins.push_back(WinInterface{
            std::stoi(result[i]),
            std::stoi(result[i + 1]),
            std::stoi(result[i + 2])});
    }
    return std::move(wins);
}

WinInterface WinDriver::getWinByUserId(int user_id) const
{
    std::vector<std::string> result = DATABASE.queryByCondition(this->table_name, "user_id = " + std::to_string(user_id));
    if (result.size() == 0)
    {
        throw std::invalid_argument("No such user");
    }
    WinInterface win;
    win.user_id = std::stoi(result[this->col]);
    win.win = std::stoi(result[this->col + 1]);
    win.total = std::stoi(result[this->col + 2]);
    return win;
}

WinInterface WinDriver::insertWin(int user_id, int win, int total) const
{
    std::string values = std::to_string(user_id) + ", " + std::to_string(win) + ", " + std::to_string(total);
    DATABASE.insert(this->table_name, "user_id, win, total", values);
    return this->getWinByUserId(user_id);
}

bool WinDriver::updateWin(int user_id, int win, int total) const
{
    DATABASE.updateByCondition(this->table_name, "win = " + std::to_string(win) + ", total = " + std::to_string(total), "user_id = " + std::to_string(user_id));
    return true;
}

const WinDriver &WinDriver::getInstance() noexcept
{
    static WinDriver instance;
    return instance;
}