#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <vector>
#include <sqlite3.h>
typedef std::vector<std::string> Record;
typedef std::vector<Record> Table;
class DatabaseConnection {
private:
    sqlite3* _db;
    sqlite3_stmt* _stmt;

public:
    DatabaseConnection(const std::string& filename);
    bool write(const std::string& params) const;
    Table readWhere(const std::string&);
    std::string quoteString(const std::string& s) const;
    ~DatabaseConnection();

};


#endif // DATABASE_H
