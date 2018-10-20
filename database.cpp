#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include "database.h"
#include <sqlite3.h>

DatabaseConnection::DatabaseConnection(const std::string& filename)
    : _db(nullptr),
      _stmt(nullptr)
    {
        int error = sqlite3_open(filename.c_str(), &_db);
        if (error) {
            throw std::logic_error("File not found!");
        }
    }

DatabaseConnection::~DatabaseConnection() {
    sqlite3_close(_db);
}

bool DatabaseConnection::write(const std::string& params) const {
    if (std::count(params.begin(), params.end(), ' ') < 5) {
        return false;
    }
    std::vector <std::string> words;
    boost::split(words, params, boost::is_any_of(" "));
    std::string sqlstmt =
            "INSERT INTO ACCOUNT (ID, PASSWORD, NAME, SURNAME, BANK, BALANCE) VALUES ("
            + quoteString(words[0]) + ","
            + quoteString(words[1]) + ","
            + quoteString(words[2]) + ","
            + quoteString(words[3]) + ","
            + quoteString(words[4]) + ","
            + quoteString(words[5]) + ");";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(_db, sqlstmt.c_str(), nullptr, nullptr, &errMsg);
    if (rc != 0) {
        throw std::logic_error(errMsg);
    }
    return true;
}

Table DatabaseConnection::readWhere(const std::string& input) {
    Table table;
    for (int i = 0; i < 6; i++) {
        table.push_back(Record());
    }
    std::string sql = "SELECT * FROM ACCOUNT WHERE " + input + ";";
    sqlite3_prepare(_db, sql.c_str(), -1, &_stmt, nullptr);
    sqlite3_step(_stmt);
    while (sqlite3_column_text(_stmt, 0)) {
        for (int i = 0; i < 6; ++i) {
            table[i].push_back(std::string((char*)sqlite3_column_text(_stmt,i) ));
        }
        sqlite3_step(_stmt);
    }
    return table;
}


std::string DatabaseConnection::quoteString(const std::string& s) const {
    return std::string("'") + s + std::string("'");
}
