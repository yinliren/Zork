//
//  Player.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include "Character.h"

class Player : public Character {
public:
    Player(const char* name, const char* description, Room* room);
    ~Player();
    
    bool Go(const std::vector<std::string>& args);
    void Look(const std::vector<std::string>& args) const;
    bool Take(const std::vector<std::string>& args);
    bool Drop(const std::vector<std::string>& args);
    void Inventory() const;
    bool Equip(const std::vector<std::string>& args);
    bool UnEquip(const std::vector<std::string>& args);
    bool Examine(const std::vector<std::string>& args) const;
    bool Attack(const std::vector<std::string>& args);
    bool Loot(const std::vector<std::string>& args);
    bool Lock(const std::vector<std::string>& args);
    bool UnLock(const std::vector<std::string>& args);
    bool Eat(const std::vector<std::string>& args);
    bool isWinning();
    bool fallCliff();
    bool inWell();
    
    public :
    std::list<Item*>* bag_;
};

#endif /* Player_h */
