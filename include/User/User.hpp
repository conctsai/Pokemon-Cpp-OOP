#pragma once

#include <string>
#include <vector>
#include "Database/UserDriver.hpp"

class UserManager
{
protected:
    UserInterface user;
    bool is_login = false;

public:
    UserManager() = default;
    bool login(const std::string &, const std::string &) noexcept;
    UserInterface getUserInterface() { return this->user; };
    void logout() noexcept;
    bool getLoginStatus() const noexcept;
    virtual int registerUser(const std::string &, const std::string &) noexcept;
    ~UserManager() = default;
};