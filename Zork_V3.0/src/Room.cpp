//
//  Room.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Globals.h"
#include "Portal.h"
#include "Character.h"
#include "Item.h"
#include "Room.h"


Room::Room(const char* title, const char* description) : GameObject(title, description, NULL) {
    type_ = ROOM;
}

Room::~Room() {}


void Room::Look() const {
    std::cout << "\n" << name_ << "\n";
    std::cout << description_;
    
    // List portals --
    for(std::list<GameObject*>::const_iterator it = container_.begin(); it != container_.cend(); ++it) {
        if((*it)->type_ == PORTAL) {
            Portal* ex = (Portal*)*it;
            std::cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->name_;
        }
    }
    
    // List items --
    for(std::list<GameObject*>::const_iterator it = container_.begin(); it != container_.cend(); ++it) {
        if((*it)->type_ == ITEM) {
            Item* item = (Item*)*it;
            std::cout << "\nThere is an item here: " << item->name_;
        }
    }
    
    // List creatures --
    for(std::list<GameObject*>::const_iterator it = container_.begin(); it != container_.cend(); ++it) {
        if((*it)->type_ == CHARACTER || (*it)->type_ == MONSTER) {
            Character* cr = (Character*)*it;
            std::cout << "\nThere is someone else here: " << cr->name_;
            if(cr->IsAlive() == false)
                std::cout << " (dead)";
        }
    }
    
    std::cout << "\n";
}


Portal* Room::GetPortal(const std::string& direction) const {
    for(std::list<GameObject*>::const_iterator it = container_.begin(); it != container_.cend(); ++it) {
        if((*it)->type_ == PORTAL)
        {
            Portal* ex = (Portal*) *it;
            if(Same(ex->GetNameFrom(this), direction))
                return ex;
        }
    }
    
    return NULL;
}


