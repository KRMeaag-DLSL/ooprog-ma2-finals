#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Database.h"

using namespace std;

Database* Database::instance = nullptr;

int main() {
    Database::getInstance()->loadData();
    return 0;
}