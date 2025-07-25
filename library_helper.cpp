//
// Created by sudosriram on 01-07-2025.
//

#include "library_helper.h"
#include "utility.h"

#include <iostream>
#include <iomanip>


void table_header() {
    std::cout << "+" << std::setw(117) << std::setfill('-') << "" << "+" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << "| " << std::left << std::setw(4) << "No."
        << " | " << std::left << std::setw(50) << "Title"
        << " | " << std::left << std::setw(20) << "Author"
        << " | " << std::left << std::setw(5) << "Pages"
        << " | " << std::left << std::setw(6) << "Copies"
        << " | " << std::left << std::setw(15) << "ISBN"
        << " |";
    std::cout << std::endl;
    std::cout << "+" << std::setw(117) << std::setfill('-') << "" << "+" << std::endl;
    std::cout << std::setfill(' ');
}


void table_footer() {
    std::cout << "+" << std::setw(117) << std::setfill('-') << "" << "+" << std::endl;
    std::cout << std::setfill(' ');
}



bool confirm() {
    std::string confirm;
    std::cout << "Confirm delete (Y/n): ";
    std::cin >> confirm;
    lowercase(confirm);
    if (confirm == "y") {
        return true;
    }
    return false;
}

int todelete() {
    int num;
    std::cout << "Enter the number of the book you want to delete (or 0 to cancel): ";
    std::cin >> num;
    if (num == 0) {
        return 0;
    }
    return num;

}

bool checkValid(int index, int size) {
    if (index >= 0 && index <= size) {
        return true;
    }
    return false;
}







