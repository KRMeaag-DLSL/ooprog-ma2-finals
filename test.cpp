#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Database.h"
#include "Students.h"
#include "Users.h"

using namespace std;

Database* Database::instance = nullptr;

int main() {
    Student student("2024178625");

    student.menu();
}