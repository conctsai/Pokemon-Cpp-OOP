#include "Database/Database.hpp"

// 数据库驱动类

Database::Database()
{
    if (sqlite3_open(db_name, &db) != SQLITE_OK)
    {
        exit(-1);
    }
}

const Database &Database::getInstance()
{
    static Database instance;
    return instance;
}

std::vector<std::string> Database::queryAll(const std::string &table_name) const
{
    char **dbResult;
    int nRow, nColumn;
    std::string querySQL = "SELECT * FROM " + table_name + ";";
    if (sqlite3_get_table(this->db, querySQL.c_str(), &dbResult, &nRow, &nColumn, NULL) != SQLITE_OK)
    {
        exit(-1);
    }

    std::vector<std::string> result;
    for (int i = 0; i < nRow + 1; i++)
    {
        for (int j = 0; j < nColumn; j++)
        {
            result.push_back(dbResult[i * nColumn + j]);
        }
    }

    sqlite3_free_table(dbResult);

    return std::move(result);
}

std::vector<std::string> Database::queryByCondition(const std::string &table_name, const std::string &condition) const
{
    char **dbResult;
    int nRow, nColumn;
    std::string querySQL = "SELECT * FROM " + table_name + " WHERE " + condition + ";";
    if (sqlite3_get_table(this->db, querySQL.c_str(), &dbResult, &nRow, &nColumn, NULL) != SQLITE_OK)
    {
        exit(-1);
    }

    std::vector<std::string> result;
    for (int i = 0; i < nRow + 1; i++)
    {
        for (int j = 0; j < nColumn; j++)
        {
            result.push_back(dbResult[i * nColumn + j]);
        }
    }

    sqlite3_free_table(dbResult);

    return std::move(result);
}

bool Database::insert(const std::string &table_name, const std::string &columns, const std::string &values) const
{
    std::string querySQL = "INSERT INTO " + table_name + " (" + columns + ") VALUES (" + values + ");";
    if (sqlite3_exec(this->db, querySQL.c_str(), NULL, NULL, NULL) != SQLITE_OK)
    {
        exit(-1);
    }
    return true;
}

bool Database::deleteByCondition(const std::string &table_name, const std::string &condition) const
{
    std::string querySQL = "DELETE FROM " + table_name + " WHERE " + condition + ";";
    if (sqlite3_exec(this->db, querySQL.c_str(), NULL, NULL, NULL) != SQLITE_OK)
    {
        exit(-1);
    }
    return true;
}

bool Database::updateByCondition(const std::string &table_name, const std::string &new_value, const std::string &condition) const
{
    std::string querySQL = "UPDATE " + table_name + " SET " + new_value + " WHERE " + condition + ";";
    if (sqlite3_exec(this->db, querySQL.c_str(), NULL, NULL, NULL) != SQLITE_OK)
    {
        exit(-1);
    }
    return true;
}

Database::~Database()
{
    sqlite3_close(db);
}
