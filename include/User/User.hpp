#pragma once

#include <string>
#include <vector>
#include "Database/UserDriver.hpp"

class UserManager
{
private:
    UserInterface user;
    bool is_login = false;

public:
    UserManager() = default;
    bool login(const std::string &, const std::string &) noexcept;
    void logout() noexcept;
    bool getLoginStatus() const noexcept;
    bool registerUser(const std::string &, const std::string &) noexcept;
    ~UserManager() = default;
};