//
//  Globals.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Globals_h
#define Globals_h

#include <string>
#include <vector>


bool Same(const std::string& a, const std::string& b);
bool Same(const char* a, const std::string& b);
bool Same(const std::string& a, const char* b);
int Roll(int min, int max);
void Tokenize(const std::string& line, std::vector<std::string>& arguments);


#endif /* Globals_h */
