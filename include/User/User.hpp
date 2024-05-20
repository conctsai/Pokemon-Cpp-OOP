#pragma once

#include <string>
#include <vector>

#define USERDRIVER UserDriver::getInstance()

struct UserInterface
{
    int id;
    std::string username;
    std::string password_hash;
};

// 单例用户数据库驱动类
class UserDriver
{
private:
    UserDriver() = default;
    UserDriver(const UserDriver &) = delete;
    UserDriver(UserDriver &&) = delete;
    UserDriver &operator=(const UserDriver &) = delete;
    const char *table_name = "users";
    int col = 3;
    const std::string col_name[3] = {"id", "username", "password_hash"};

public:
    ~UserDriver() = default;
    std::vector<UserInterface> getAllUsers() const noexcept;
    UserInterface getUserByUsername(const std::string &) const;
    UserInterface getUserById(int) const;
    UserInterface insertUser(const std::string &, const std::string &) const;
    static const UserDriver &getInstance() noexcept;
};

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