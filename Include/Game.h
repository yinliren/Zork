//
//  Game.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include <string>
#include <list>
#include <time.h>
#include "Player.h"
#define TICK_FREQUENCY 0.5f

class GameObject;
class Player;

class Game {
    public :
    
    Game();
    ~Game();
    
    bool Tick(std::vector<std::string>& args);
    bool Parser(std::vector<std::string>& args);
    void GameLoop();
    
    clock_t tick_timer_;
    std::list<GameObject*> gameObject_;
    Player* player_;
};


#endif /* Game_h */
