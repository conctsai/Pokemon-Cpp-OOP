#include "User/User.hpp"

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