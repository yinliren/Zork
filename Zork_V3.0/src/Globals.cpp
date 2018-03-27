//
//  Globals.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include "Globals.h"
bool Same(const std::string& a, const std::string& b) {
    return strcmp(a.c_str(), b.c_str()) == 0;
}

bool Same(const char* a, const std::string& b) {
    return strcmp(a, b.c_str()) == 0;
}

bool Same(const std::string& a, const char* b) {
    return strcmp(a.c_str(), b) == 0;
}

int Roll(int min, int max) {
    if (max > 0) return min + (rand() % (max - min));
    else return 0;
}

void Tokenize(const std::string& line, std::vector<std::string>& arguments) {
    const char* str = line.c_str();
    do
    {
        const char *begin = str;
        
        while(*str != ' ' && *str)
            str++;
        
        arguments.push_back(std::string(begin, str));
    } while(0 != *str++);
}

