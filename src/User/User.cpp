#include "User/user.hpp"
#include "Database/database.hpp"
#include "Utils/utils.hpp"
#include <stdexcept>

const UserDriver &UserDriver::getInstance() noexcept
{
    static UserDriver instance;
    return instance;
}

std::vector<UserInterface> UserDriver::getAllUsers() const noexcept
{
    std::vector<UserInterface> users;
    std::vector<std::string> result = std::move(DATABASE.queryAll(this->table_name));
    for (int i = this->col; i < result.size(); i += this->col)
    {
        users.push_back(UserInterface{
            std::stoi(result[i]),
            result[i + 1],
            result[i + 2]});
    }
    return std::move(users);
}

UserInterface UserDriver::getUserByUsername(const std::string &username) const
{
    std::vector<std::string> result = std::move(DATABASE.queryByCondition(this->table_name, "username = '" + username + "'"));

    if (result.size() == 0)
    {
        throw std::invalid_argument("User not found");
    }

    return UserInterface{
        std::stoi(result[this->col]),
        result[this->col + 1],
        result[this->col + 2]};
}

UserInterface UserDriver::getUserById(int id) const
{
    std::vector<std::string> result = std::move(DATABASE.queryByCondition(this->table_name, "id = " + std::to_string(id)));

    if (result.size() == 0)
    {
        throw std::invalid_argument("User not found");
    }

    return UserInterface{
        std::stoi(result[this->col]),
        result[this->col + 1],
        result[this->col + 2]};
}

UserInterface UserDriver::insertUser(const std::string &username, const std::string &password) const
{
    try
    {
        this->getUserByUsername(username);
    }
    catch (const std::invalid_argument &e)
    {
        std::string password_hash = utils::getSHA256(password);
        std::string values = "'" + username + "', '" + password_hash + "'";
        DATABASE.insert(this->table_name, "username, password_hash", values);
        return this->getUserByUsername(username);
    }
    throw std::invalid_argument("User already exists");
}

bool UserManager::login(const std::string &username, const std::string &password) noexcept
{
    try
    {
        UserInterface user = USERDRIVER.getUserByUsername(username);
        if (user.password_hash == utils::getSHA256(password))
        {
            this->user = user;
            this->is_login = true;
            return true;
        }
        else
        {
            return false;
        }
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
}

bool UserManager::getLoginStatus() const noexcept
{
    return this->is_login;
}

void UserManager::logout() noexcept
{
    this->is_login = false;
}

bool UserManager::registerUser(const std::string &username, const std::string &password) noexcept
{
    try
    {
        USERDRIVER.insertUser(username, password);
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
}