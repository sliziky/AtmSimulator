#ifndef HANDLER_H
#define HANDLER_H
#include <iostream>
#include "database.h"
#include <vector>
#include <memory>
typedef std::vector<std::string> Record;
typedef std::vector<Record> Table;
class Handler
{
private:
    DatabaseConnection _db;
    void mainMenu() const;
    void signInMenu();
    int intInput(const std::string& info) const;
    void evaluate(int choice);

    friend std::ostream& operator<<(std::ostream& in, Table& table);
    bool accountExists(int id, int pw,const Table& table) const;
    bool correctPassword(int id, int pw, const Table& table) const;
public:
    Handler() : _db("/home/peter/cpp/atmSimulator/database.db") {}
    void start();

};



#endif // HANDLER_H
