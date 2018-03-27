//
//  Item.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Room.h"
#include "Portal.h"
#include "Globals.h"
#include "Item.h"

Item::Item(const char* title, const char* description, GameObject* parent, ItemType item_type) :
GameObject(title, description, parent), item_type_(item_type) {
    type_ = ITEM;
    min_value_ = max_value_ = 0;
}


Item::~Item() {}

void Item::Look() const
{
    std::cout << "\n" << name_ << "\n";
    std::cout << description_ << "\n";
    
    std::list<GameObject*> stuff;
    FindAll(ITEM, stuff);
    
    if(stuff.size() > 0)
    {
        std::cout << "It contains: " << "\n";
        for(std::list<GameObject*>::const_iterator it = stuff.begin(); it != stuff.cend(); ++it)
            std::cout << (*it)->name_ << "\n";
    }
}


int Item::GetValue() const {
    return Roll(min_value_, max_value_);
}

