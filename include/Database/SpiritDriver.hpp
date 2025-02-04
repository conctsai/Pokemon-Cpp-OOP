#pragma once

#include "Database/Database.hpp"
#include <vector>
#include "User/User.hpp"

#define SPIRITDRIVER SpiritDirver::getInstance()

struct SpiritInterface
{
    int id;
    int user_id;
    std::string spirit_json;
};

class SpiritDirver
{
private:
    SpiritDirver() = default;
    SpiritDirver(const SpiritDirver &) = delete;
    SpiritDirver(SpiritDirver &&) = delete;
    SpiritDirver &operator=(const SpiritDirver &) = delete;
    const char *table_name = "spirits";
    int col = 3;
    const std::string col_name[3] = {"id", "user_id", "spirit_json"};

public:
    std::vector<SpiritInterface> getAllSpirits() const noexcept;
    std::vector<SpiritInterface> getSpiritsByUserId(int user_id) const;
    SpiritInterface getSpiritById(int id) const;
    SpiritInterface insertSpirit(int user_id, const std::string &spirit_json) const;
    bool deleteSpirit(int id) const;
    bool UpdateSpirit(int id, const std::string &spirit_json) const;
    ~SpiritDirver() = default;
    static const SpiritDirver &getInstance() noexcept;
};

// 建表语句
// CREATE TABLE spirits(
//     id integer primary key,
//     user_id integer not null,
//     spirit_json text not null)