#include <iostream>
#include "handler.h"


void Handler::start() {
    int choice;
    for (;;) {
        mainMenu();
        std::cin >> choice;
        if(choice == 0) {
            return;
        }
        evaluate(choice);
    }
}


void Handler::mainMenu() const {
    std::cout << "==============" << std::endl;
    std::cout << "= 0. Exit    =" << std::endl;
    std::cout << "= 1. Sign up =" << std::endl;
    std::cout << "= 2. Sign in =" << std::endl;
    std::cout << "==============" << std::endl;

}

void Handler::evaluate(int choice) {

    if (choice == 2) {
        signInMenu();
    }
}

std::ostream& operator<<(std::ostream& in, Table& table) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < table[i].size(); ++j) {
            switch(i) {
                case 0: std::cout << "ID: "; break;
                case 1: std::cout << "PW: "; break;
                case 2: std::cout << "Name: "; break;
                case 3: std::cout << "Surname: "; break;
                case 4: std::cout << "Bank: "; break;
                case 5: std::cout << "Balance: "; break;
            }
            in << table[i][j] << std::endl;
         }
    }
    return in;
}

void Handler::signInMenu(){
    int id = intInput("ID:");
    int pw = intInput("Password:");
    Table table =_db.readWhere("ID = " + std::to_string(id));
    if (!accountExists(id, pw, table)) {
        std::cerr << "Account NOT FOUND / WRONG PASSWORD" << std::endl;
    }
    else {
        std::cout << table ;
    }
}

int Handler::intInput(const std::string& info) const {
    int x;
    std::cout << info << std::endl;
    std::cin >> x;
    return x;
}

bool Handler::accountExists(int id, int pw, const Table& table) const {
    if (table[0].empty()) {
        return false;
    }
    for (int i = 0; i < table[0].size(); ++i) {
        if ((std::stoi(table[0][i]) == id) && std::stoi(table[1][i]) == pw) {
            return true;
        }
    }
    return false;
}


