//
//  Monster.h
//  Zork_V3.0
//
//  Created by Liren on 12/17/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Monster_h
#define Monster_h
#include "Character.h"

class Monster : public Character {
public:
    Monster(const char* name, const char* description, Room* room);
    ~Monster();
    
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
    
};




#endif /* Monster_h */
