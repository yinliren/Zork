//
//  Character.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Globals.h"
#include "Room.h"
#include "Portal.h"
#include "Item.h"
#include "Character.h"

Character::Character(const char* title, const char* description, Room* room) :
GameObject(title, description, (GameObject*)room)
{
    type_ = CHARACTER;
    hit_points_ = 1;
    min_damage_ = max_damage_ = min_protection_ = max_protection_ = 0;
    weapon_ = armour_ = NULL;
    combat_target_ = NULL;
}


Character::~Character()
{}


void Character::Look(const std::vector<std::string>& args) const {
    if(IsAlive())
    {
        std::cout << name_ << "\n";
        std::cout << description_ << "\n";
    }
    else
    {
        std::cout << name_ << "'s corpse\n";
        std::cout << "Here lies dead: " << description_ << "\n";
    }
}


bool Character::Go(const std::vector<std::string>& args) {
    if(!IsAlive())
        return false;
    
    Portal* portal = GetRoom()->GetPortal(args[1]);
    
    if(portal == NULL)
        return false;
    
    if(PlayerInRoom())
        std::cout << name_ << "goes " << args[1] << "...\n";
    
    ChangeParentTo(portal->GetDestinationFrom((Room*) parent_));
    
    return true;
}


bool Character::Take(const std::vector<std::string>& args) {
    if(!IsAlive())
        return false;
    
    Item* item = (Item*)parent_->Find(args[1], ITEM);
    
    if(args.size() > 1)
    {
        // we could pick something from a container in our inventory ...
        if(item == NULL)
            item = (Item*)Find(args[1], ITEM);
        
        if(item == NULL)
            return false;
        
        Item* subitem = (Item*)item->Find(args[3], ITEM);
        
        if(subitem == NULL)
            return false;
        
        if(PlayerInRoom())
            std::cout << name_ << " looks into " << item->name_ << "...\n";
        
        item = subitem;
    }
    
    if(item == NULL)
        return false;
    
    if(PlayerInRoom())
        std::cout << name_ << " takes " << item->name_ << ".\n";
    
    item->ChangeParentTo(this);
    
    return true;
}


void Character::Inventory() const {
    std::list<GameObject*> items;
    FindAll(ITEM, items);
    
    if(items.size() == 0)
    {
        std::cout << name_ << " does not own any items\n";
        return;
    }
    
    std::cout << "\n" << name_ << " owns:\n";
    for(std::list<GameObject*>::const_iterator it = items.begin(); it != items.cend(); ++it)
    {
        if(*it == weapon_)
            std::cout << (*it)->name_ << " (as weapon)\n";
        else if(*it == armour_)
            std::cout << (*it)->name_ << " (as armour)\n";
        else
            std::cout << (*it)->name_ << "\n";
    }
}


bool Character::Equip(const std::vector<std::string>& args) {
    if(!IsAlive())
        return false;
    
    Item* item = (Item*)Find(args[1], ITEM);
    
    if(item == NULL)
        return false;
    
    switch(item->type_) {
        case WEAPON:
            weapon_ = item;
            break;
            
        case ARMOUR:
            armour_ = item;
            break;
            
        default:
            return false;
    }
    
    if(PlayerInRoom())
        std::cout << name_ << " equips " << item->name_ << "...\n";
    
    return true;
}


bool Character::UnEquip(const std::vector<std::string>& args) {
    if(!IsAlive())
        return false;
    
    Item* item = (Item*)Find(args[1], ITEM);
    
    if(item == NULL)
        return false;
    
    if(item == weapon_)
        weapon_ = NULL;
    else if(item == weapon_)
        armour_ = NULL;
    else
        return false;
    
    if(PlayerInRoom())
        std::cout << name_ << " un-equips " << item->name_ << "...\n";
    
    return true;
}



bool Character::AutoEquip() {
    if(!IsAlive())
        return false;
    
    std::list<GameObject*> items;
    FindAll(ITEM, items);
    
    for(std::list<GameObject*>::const_iterator it = items.begin(); it != items.cend(); ++it)
    {
        Item* i = (Item*)(*it);
        
        if(i->item_type_ == WEAPON)
            weapon_ = i;
        if(i->item_type_ == ARMOUR)
            armour_ = i;
    }
    
    return true;
}


bool Character::Lock(const std::vector<std::string>& args) {
    if(!IsAlive())
        return false;
    
    Portal* portal = GetRoom()->GetPortal(args[1]);
    
    if(portal == NULL || portal->locked_ == true)
        return false;
    
    Item* item = (Item*)Find(args[3], ITEM);
    
    if(item == NULL || portal->key_ != item)
        return false;
    
    if(PlayerInRoom())
        std::cout << "\n" << name_ << "locks " << portal->GetNameFrom((Room*)parent_) << "...\n";
    
    portal->locked_ = true;
    
    return true;
}


bool Character::UnLock(const std::vector<std::string>& args) {
    if(!IsAlive())
        return false;
    
    Portal* portal = GetRoom()->GetPortal(args[1]);
    
    if(portal == NULL || portal->locked_ == false)
        return false;
    
    Item* item = (Item*)Find(args[3], ITEM);
    
    if(item == NULL || portal->key_ != item)
        return false;
    
    if(PlayerInRoom())
        std::cout << "\n" << name_ << "unlocks " << portal->GetNameFrom((Room*) parent_) << "...\n";
    
    portal->locked_ = false;
    
    return true;
}


bool Character::Drop(const std::vector<std::string>& args) {
    if(!IsAlive())
        return false;
    
    Item* item = (Item*)Find(args[1], ITEM);
    
    if(item == NULL)
        return false;
    
    if(PlayerInRoom())
        std::cout << name_ << " drops " << item->name_ << "...\n";
    
    item->ChangeParentTo(parent_);
    
    return true;
}


Room* Character::GetRoom() const {
    return (Room*)parent_;
}


bool Character::PlayerInRoom() const {
    return parent_->Find(PLAYER) != NULL;
}


bool Character::IsAlive() const {
    return hit_points_ > 0;
}


void Character::Tick() {
    if(combat_target_ != NULL)
    {
        if(parent_->Find(combat_target_) == true)
            MakeAttack();
        else
            combat_target_ = NULL;
    }
}


bool Character::Attack(const std::vector<std::string>& args) {
    Character *target = (Character*)parent_->Find(args[1], CHARACTER);
    
    if(target == NULL)
        return false;
    
    combat_target_ = target;
    std::cout << "\n" << name_ << " attacks " << target->name_ << "!\n";
    return true;
}


int Character::MakeAttack() {
    if(!IsAlive() || !combat_target_->IsAlive())
    {
        combat_target_ = combat_target_->combat_target_ = NULL;
        return false;
    }
    
    int result = (weapon_) ? weapon_->GetValue() : Roll(min_damage_, max_damage_);
    
    if(PlayerInRoom())
        std::cout << name_ << " attacks " << combat_target_->name_ << " for " << result << "\n";
    
    combat_target_->ReceiveAttack(result);
    
    // make the attacker react and take me as a target
    if(combat_target_->combat_target_ == NULL)
        combat_target_->combat_target_ = this;
    
    return result;
}


int Character::ReceiveAttack(int damage) {
    int prot = (armour_) ? armour_->GetValue() : Roll(min_protection_, max_protection_);
    int received = damage - prot;
    received = (received < 0 ? 0 : received);
    
    int real_blocked;
    real_blocked = (damage <= prot ? damage : prot);
    
    hit_points_ -= received;
    if (hit_points_ < 0) hit_points_ = 0;
    if(PlayerInRoom())
        std::cout << name_ << " is hit for " << received << " damage (" << real_blocked << " blocked) \n";
    
    if(IsAlive() == false)
        Die();
    
    return received;
}


void Character::Die() {
    if(PlayerInRoom())
        std::cout << name_ << " dies.\n";
}


bool Character::Loot(const std::vector<std::string>& args) {
    Character *target = (Character*)parent_->Find(args[1], CHARACTER);
    
    if(target == NULL && target->IsAlive() == false)
        return false;
    
    std::list<GameObject*> items;
    target->FindAll(ITEM, items);
    
    for(std::list<GameObject*>::const_iterator it = items.begin(); it != items.cend(); ++it)
    {
        Item* i = (Item*)(*it);
        i->ChangeParentTo(this);
    }
    
    std::cout << "\n" << name_ << " loots " << target->name_ << "'s corpse\n";
    
    return true;
}


void Character::Stats() const {
    std::cout << "\nHit Points: " << hit_points_;
    std::cout << "\nAttack: (" << ((weapon_) ? weapon_->name_ : "no weapon") << ") ";
    std::cout << ((weapon_) ? weapon_->min_value_ : min_damage_) << "-" << ((weapon_) ? weapon_->max_value_ : max_damage_);
    std::cout << "\nProtection: (" << ((armour_) ? armour_->name_ : "no armour") << ") ";
    std::cout << ((armour_) ? armour_->min_value_ : min_protection_) << "-" << ((armour_) ? armour_->max_value_ : max_protection_);
    std::cout << "\n";
}

