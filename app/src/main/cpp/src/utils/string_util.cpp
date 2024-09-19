//
// Created by 86177 on 2024/9/13.
//

#include <string>
#include "string_util.hpp"

bool is_number(const char *str) {
    std::string name(str);
    for (char c: name) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int str_to_int(const char *str) {
    if (!is_number(str)) {
        return -1;
    }
    std::string name(str);
    return stoi(name);
}