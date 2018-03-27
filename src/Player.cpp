//
//  Player.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <list>
#include "Globals.h"
#include "Player.h"
#include "Room.h"
#include "Portal.h"
#include "Item.h"
#include "Apple.h"

Player::Player(const char* title, const char* description, Room* room) :
Character(title, description, room) {
    type_ = PLAYER;
    bag_ = new std::list<Item*>();
}

Player::~Player() {}

void Player::Look(const std::vector<std::string>& args) const {
    if(args.size() > 1) {
        for(std::list<GameObject*>::const_iterator it = parent_->container_.begin(); it != parent_->container_.cend(); ++it)
        {
            if(Same((*it)->name_, args[1]) || ((*it)->type_ == PORTAL && Same(args[1], ((Portal*)(*it))->GetNameFrom((Room*)parent_)))) {
                (*it)->Look();
                return;
            }
        }

        
        if(Same(args[1], "me")) {
            std::cout << "\n" << name_ << "\n";
            std::cout << description_ << "\n";
        }
    }
    else {
        parent_->Look();
    }
}


bool Player::Go(const std::vector<std::string>& args) {
    Portal* portal = GetRoom()->GetPortal(args[1]);
    
    if(portal == NULL) {
        std::cout << "\nThere is no portal at '" << args[1] << "'.\n";
        return false;
    }
    
    if(portal->locked_) {
        std::cout << "\nThat portal is locked.\n";
        std::cout << "Command Format: unlock [portal direction (east, west, up, down etc..)] with [name of key]\n";
        return false;
    }
    
    std::cout << "\nYou take direction " << portal->GetNameFrom((Room*) parent_) << "...\n";
    ChangeParentTo(portal->GetDestinationFrom((Room*) parent_));
    parent_->Look();
    
    return true;
}



bool Player::Take(const std::vector<std::string>& args) {
    if(args.size() == 4)
    {
        Item* item = (Item*)parent_->Find(args[3], ITEM);
        
        // we could pick something from a container in our inventory ...
        if(item == NULL) {
            item = (Item*)Find(args[3], ITEM);
        }
        
        if(item == NULL)
        {
            std::cout << "\nCannot find '" << args[3] << "' in this room or in your inventory.\n";
            return false;
        }
        
        Item* subitem = (Item*)item->Find(args[1], ITEM);
        
        if(subitem == NULL) {
            std::cout << "\n" << item->name_ << " does not contain '" << args[1] << "'.\n";
            return false;
        }
        
        std::cout << "\nYou take " << subitem->name_ << " from " << item->name_ << ".\n";
        subitem->ChangeParentTo(this);
    }
    else if(args.size() == 2) {
        Item* item = (Item*)parent_->Find(args[1], ITEM);
        
        if(item == NULL) {
            std::cout << "\nThere is no item here with that name.\n";
            return false;
        }
        
        std::cout << "\nYou take " << item->name_ << ".\n";
        item->ChangeParentTo(this);
    }
    
    return false;
}


void Player::Inventory() const
{
    std::list<GameObject*> items;
    FindAll(ITEM, items);
    
    if(items.size() == 0) {
        std::cout << "\nYou do not own any item.\n";
        return;
    }
    
    for(std::list<GameObject*>::const_iterator it = items.begin(); it != items.cend(); ++it)
    {
        if(*it == weapon_) std::cout << "\n" << (*it)->name_ << " (as weapon)";
        else if(*it == armour_) std::cout << "\n" << (*it)->name_ << " (as armour)";
        else std::cout << "\n" << (*it)->name_;
    }
    
    std::cout << "\n";
}


bool Player::Drop(const std::vector<std::string>& args) {
    if(args.size() == 2) {
        Item* item = (Item*)Find(args[1], ITEM);
        
        if(item == NULL) {
            std::cout << "\nThere is no item on you with that name.\n";
            return false;
        }
        
        std::cout << "\nYou drop " << item->name_ << "...\n";
        item->ChangeParentTo(parent_);
        
        return true;
    }
    else if(args.size() == 4) {
        Item* item = (Item*)Find(args[1], ITEM);
        
        if(item == NULL) {
            std::cout << "\nCan not find '" << args[1] << "' in your inventory.\n";
            return false;
        }
        
        Item* container = (Item*)parent_->Find(args[3], ITEM);
        
        if(container == NULL) {
            container = (Item*)Find(args[3], ITEM);
            std::cout << "\nCan not find '" << args[3] << "' in your inventory or in the room.\n";
            return false;
        }
        
        std::cout << "\nYou put " << item->name_ << " into " << container->name_ << ".\n";
        item->ChangeParentTo(container);
        
        return true;
    }
    
    return false;
}


bool Player::Equip(const std::vector<std::string>& args) {
    Item* item = (Item*)Find(args[1], ITEM);
    if(item == NULL) {
        std::cout << "\nCannot find '" << args[1] << "' is not in your inventory.\n";
        return false;
    }
    
    switch(item->item_type_)
    {
        case WEAPON:
            weapon_ = item;
            break;
            
        case ARMOUR:
            armour_ = item;
            break;
            
        default:
            std::cout << "\n" << item->name_ << " cannot be equipped.\n";
            return false;
    }
    
    std::cout << "\nYou equip " << item->name_ << "...\n";
    
    return true;
}


bool Player::UnEquip(const std::vector<std::string>& args)
{
    if(!IsAlive()) return false;
    
    Item* item = (Item*)Find(args[1], ITEM);
    
    if(item == NULL) {
        std::cout << "\n" << item->name_ << " is not in your inventory.\n";
        return false;
    }
    
    if(item == weapon_) {
        weapon_ = NULL;
    }
    else if(item == armour_) {
        armour_ = NULL;
    }
    
    else {
        std::cout << "\n" << item->name_ << " is not equipped.\n";
        return false;
    }
    
    std::cout << "\nYou un-equip " << item->name_ << "...\n";
    
    return true;
}


bool Player::Examine(const std::vector<std::string>& args) const {
    Character* target_character = (Character*)parent_->Find(args[1], CHARACTER);
    Character* target_monster = (Character*)parent_->Find(args[1], MONSTER);
    if(target_character == nullptr && target_monster == nullptr) {
        std::cout << "\n" << args[1] << " is not here.\n";
        return false;
    }
    
    if (target_character != nullptr && target_monster == nullptr) {
        if (target_character->IsAlive()){
            target_character->Inventory();
            target_character->Stats();
        }
        else {
            target_character->Inventory();
        }
    }
    
    if (target_monster != nullptr) {
        if (target_monster->IsAlive()) {
            std::cout << "\nYou are attcked by " << target_monster->name_ << "!\n";
            target_monster->Stats();
            target_monster->MakeAttack();
        }
        else {
            target_monster->Stats();
        }
    }
    return true;
}


bool Player::Attack(const std::vector<std::string>& args) {
    Character* target_character = (Character*)parent_->Find(args[1], CHARACTER);
    Character* target_monster = (Character*)parent_->Find(args[1], MONSTER);
    int weapon_damage = 0;
    if(weapon_ != NULL) weapon_damage = weapon_->GetValue();
    int real_damage = Roll(min_damage_, max_damage_) + weapon_damage;
    
    if(target_character == NULL && target_monster == NULL) {
        std::cout << "\n" << args[1] << " is not here.";
        return false;
    }
    
    if (target_character != NULL) {
        combat_target_ = target_character;
        std::cout << "\nYou jump to attack " << target_character->name_ << "!\n";
        target_character->ReceiveAttack(real_damage);
        if (target_character->IsAlive()) {
            target_character->MakeAttack();
        }
        return true;
    }
    
    if (target_monster != NULL) {
        combat_target_ = target_monster;
        std::cout << "\nYou jump to attack " << target_monster->name_ << "!\n";
        target_monster->ReceiveAttack(real_damage);
        if (target_monster->IsAlive()) {
            target_monster->MakeAttack();
        }
        return true;
    }
    return true;
}


bool Player::Loot(const std::vector<std::string>& args)
{
    Character *target = (Character*)parent_->Find(args[1], CHARACTER);
    Character *target_monster = (Character*)parent_->Find(args[1], MONSTER);
    
    if (target == NULL && target_monster == NULL) {
        std::cout << "\n" << args[1] << " is not here.\n";
        return false;
    }
    
    if (target != NULL) {
        if(target->IsAlive()) {
            std::cout << "\n" << target->name_ << " cannot be looted until it is killed.\n";
            return false;
        }
    }
    
    if (target_monster != NULL) {
        if(target_monster->IsAlive()) {
            std::cout << "\n" << target_monster->name_ << " cannot be looted until it is killed.\n";
            return false;
        }
    }
    
    
    
    if (target != NULL) {
        std::list<GameObject*> items;
        target->FindAll(ITEM, items);
        if(items.size() > 0) {
            std::cout << "\nYou loot " << target->name_ << "'s corpse:\n";
            
            for(std::list<GameObject*>::const_iterator it = items.begin(); it != items.cend(); ++it) {
                Item* i = (Item*)(*it);
                std::cout << "You find: " << i->name_ << "\n";
                i->ChangeParentTo(this);
            }
        }
        else
            std::cout << "\nYou loot " << target->name_ << "'s corpse, but find nothing there.\n";
        return true;
    }
    
    if (target_monster != NULL) {
        std::list<GameObject*> items;
        target_monster->FindAll(ITEM, items);
        if(items.size() > 0) {
            std::cout << "\nYou loot " << target_monster->name_ << "'s corpse:\n";
            
            for(std::list<GameObject*>::const_iterator it = items.begin(); it != items.cend(); ++it) {
                Item* i = (Item*)(*it);
                std::cout << "You find: " << i->name_ << "\n";
                i->ChangeParentTo(this);
            }
        }
        else
            std::cout << "\nYou loot " << target_monster->name_ << "'s corpse, but find nothing there.\n";
        return true;
    }
    return true;
}


bool Player::Lock(const std::vector<std::string>& args)
{
    if(!IsAlive())
        return false;
    
    Portal* portal = GetRoom()->GetPortal(args[1]);
    
    if(portal == NULL)
    {
        std::cout << "\nThere is no portal at '" << args[1] << "'.\n";
        return false;
    }
    
    if(portal->locked_ == true)
    {
        std::cout << "\nThat portal is already locked.\n";
        return false;
    }
    
    Item* item = (Item*)Find(args[3], ITEM);
    
    if(item == NULL)
    {
        std::cout << "\nItem '" << args[3] << "' not found in your inventory.\n";
        return false;
    }
    
    if(portal->key_ != item)
    {
        std::cout << "\nItem '" << item->name_ << "' is not the key for " << portal->GetNameFrom((Room*)parent_) << ".\n";
        return false;
    }
    
    std::cout << "\nYou lock " << portal->GetNameFrom((Room*)parent_) << "...\n";
    
    portal->locked_ = true;
    
    return true;
}


bool Player::UnLock(const std::vector<std::string>& args) {
    if(!IsAlive())
        return false;
    
    Portal* portal = GetRoom()->GetPortal(args[1]);
    
    if(portal == NULL){
        std::cout << "\nThere is no portal at '" << args[1] << "'.\n";
        return false;
    }
    
    if(portal->locked_ == false) {
        std::cout << "\nThat portal is not locked.\n";
        return false;
    }
    
    Item* item = (Item*)Find(args[3], ITEM);
    
    if(item == NULL) {
        std::cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
        return false;
    }
    
    if(portal->key_ != item) {
        std::cout << "\nKey '" << item->name_ << "' is not the key for " << portal->GetNameFrom((Room*)parent_) << ".\n";
        return false;
    }
    
    std::cout << "\nYou unlock " << portal->GetNameFrom((Room*)parent_) << "...\n";
    
    portal->locked_ = false;
    
    return true;
}

bool Player::Eat(const std::vector<std::string>& args) {
    Item* item = (Item*)Find(args[1], ITEM);
    if(item == NULL) {
        std::cout << "\nCannot find '" << args[1] << "' is not in your inventory.\n";
        return false;
    }
    
    switch(item->item_type_)
    {
        case HEALTH_EAT:
            hit_points_ += item->health_recover_;
            std::cout << "\nYou eat " << item->name_ << "...\n";
            break;
            
        case HEALTH_DRINK:
            hit_points_ += item->health_recover_;
            std::cout << "\nYou eat " << item->name_ << "...\n";
            break;
            
        default:
            std::cout << "\n" << item->name_ << " cannot be eaten.\n";
            return false;
    }
    return true;
}


bool Player::isWinning() {
    return parent_->name_ == "WhiteCastle";
}

bool Player::fallCliff() {
    return parent_->name_ == "CliffBottom";
}

bool Player::inWell() {
    return parent_->name_ == "Well";
}
