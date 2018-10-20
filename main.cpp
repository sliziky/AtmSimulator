#include <iostream>
#include "database.h"
#include "handler.h"
using namespace std;

int main()
{

    Handler handler;
    try {
        handler.start();}
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
