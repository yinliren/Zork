//
//  main.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "Globals.h"
#include "Game.h"

// -------------------------------------------------
int main(int argc, const char * argv[])
{
    
    std::vector<std::string> args;
    args.reserve(10);
    
    std::cout << "Welcome to MyZork!\n";
    std::cout << "----------------\n";
    std::cout << "Type: look (To see what's around you)\n";

    Game my_game;
    
    while (true) {
        if (!my_game.player_->IsAlive()) {
            std::cout << "You are dead. Game Over.";
            break;
        }
        //my_game.player_->parent_ == (Room*)Castle
        if (my_game.player_->isWinning()) {
            std::cout << "You reached the Castle safely. You are a WINNER!!!!!";
            break;
        }
        
        if (my_game.player_->fallCliff()) {
            std::cout << "You fall from a CLIFF and you are dead.";
            break;
        }
        
        if (my_game.player_->inWell()) {
            std::cout << "You fall into a well and you are drowned.";
            break;
        }
        std::string player_input;
        getline(std::cin, player_input);
        size_t pos_contains;
        
        
        if (!player_input.empty()) {
            pos_contains = player_input.find('\b');
            if (pos_contains != std::string::npos) {
                if (player_input.length() > 0) {
                    player_input.pop_back();
                    std::cout << '\b';
                    std::cout << " ";
                    std::cout << '\b';
                }
            }
            else if ((pos_contains = player_input.find('\r')) != std::string::npos) {
                player_input += '\r';
                std::cout << '\r';
            }
            else {
                Tokenize(player_input, args);
            }
        }
        
        
        pos_contains = player_input.find("quit");
        if(pos_contains != std::string::npos) {
            break;
        }
        
        if(my_game.Tick(args) == false)
            std::cout << "\nSorry, I do not understand your command.\n";
        
        if(args.size() > 0)
        {
            args.clear();
            player_input = "";
            std::cout << "> ";
        }
        
    }
    
    std::cout << "\nThanks for playing, Bye!\n";
    return 0;
}

