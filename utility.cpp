//
// Created by sudosriram on 02-07-2025.
//

#include "utility.h"

void lowercase(std::string &s) {
    for (auto &c : s) {
        c = tolower(c);
    }
}