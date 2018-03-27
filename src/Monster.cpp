//
//  Monster.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/17/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include "Monster.h"
#include "Globals.h"
#include "Room.h"
#include <iostream>

Monster::Monster(const char* name, const char* description, Room* room) : Character(name, description, room) {
    type_ = MONSTER;
}
Monster::~Monster() {}

bool Monster::Go(const std::vector<std::string>& args) {
    return false;
}
void Monster::Look(const std::vector<std::string>& args) const {
    return;
}
bool Monster::Take(const std::vector<std::string>& args) {
    return false;
}
bool Monster::Drop(const std::vector<std::string>& args) {
    return false;
}
void Monster::Inventory() const {
    return;
}
bool Monster::Equip(const std::vector<std::string>& args) {
    return false;
}
bool Monster::UnEquip(const std::vector<std::string>& args) {
    return false;
}
bool Monster::Examine(const std::vector<std::string>& args) const {
    return false;
}
bool Monster::Attack(const std::vector<std::string>& args) {
    Character *target = (Character*)parent_->Find(args[1], PLAYER);
    
    if(target == NULL)
    {
        std::cout << "\n" << args[1] << " is not here.";
        return false;
    }
    
    combat_target_ = target;
    std::cout << "\nYou are attcked by " << target->name_ << "!\n";
    return true;
}
bool Monster::Loot(const std::vector<std::string>& args) {
    return false;
}
bool Monster::Lock(const std::vector<std::string>& args) {
    return false;
}
bool Monster::UnLock(const std::vector<std::string>& args) {
    return false;
}
