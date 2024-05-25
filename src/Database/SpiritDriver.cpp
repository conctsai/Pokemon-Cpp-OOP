#include "Database/SpiritDriver.hpp"

std::vector<SpiritInterface> SpiritDirver::getAllSpirits() const noexcept
{
    std::vector<SpiritInterface> spirits;
    std::vector<std::string> result = std::move(DATABASE.queryAll(this->table_name));
    for (int i = this->col; i < result.size(); i += this->col)
    {
        spirits.push_back(SpiritInterface{
            std::stoi(result[i]),
            std::stoi(result[i + 1]),
            result[i + 2]});
    }
    return std::move(spirits);
}

std::vector<SpiritInterface> SpiritDirver::getSpiritsByUserId(int user_id) const
{
    std::vector<SpiritInterface> spirits;
    std::vector<std::string> result = std::move(DATABASE.queryByCondition(this->table_name, "user_id = " + std::to_string(user_id)));

    USERDRIVER.getUserById(user_id); // 验证用户是否存在，如果不存在则抛出异常

    for (int i = this->col; i < result.size(); i += this->col)
    {
        spirits.push_back(SpiritInterface{
            std::stoi(result[i]),
            std::stoi(result[i + 1]),
            result[i + 2]});
    }
    return std::move(spirits); // 可能返回空Vector，因为某个用户可能没有精灵
}

SpiritInterface SpiritDirver::getSpiritById(int id) const
{
    std::vector<std::string> result = std::move(DATABASE.queryByCondition(this->table_name, "id = " + std::to_string(id)));

    if (result.size() == 0)
    {
        throw std::invalid_argument("Spirit not found");
    }

    return SpiritInterface{
        std::stoi(result[this->col]),
        std::stoi(result[this->col + 1]),
        result[this->col + 2]};
}

SpiritInterface SpiritDirver::insertSpirit(int user_id, const std::string &spirit_json) const
{
    USERDRIVER.getUserById(user_id);
    DATABASE.insert(this->table_name, "user_id, spirit_json", std::to_string(user_id) + ", '" + spirit_json + "'");
    std::vector<SpiritInterface> spirits = this->getSpiritsByUserId(user_id);
    return spirits[spirits.size() - 1];
}

const SpiritDirver &SpiritDirver::getInstance() noexcept
{
    static SpiritDirver instance;
    return instance;
}