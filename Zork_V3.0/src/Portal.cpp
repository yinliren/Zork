//
//  Portal.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Portal.h"
#include "Room.h"


Portal::Portal(const char* name, const char* opposite_name, const char* description, Room* origin, Room* destination, bool one_way, bool locked) :
GameObject(name, description, (GameObject*)origin),
closed_(false), locked_(locked), key_(NULL), one_way_(one_way), destination_(destination), opposite_name_(opposite_name) {
    type_ = PORTAL;
    
    if(one_way == false)
        destination_->container_.push_back(this);
}

Portal::~Portal() {}


void Portal::Look() const {
    std::cout << name_ << " to " << opposite_name_ << "\n";
    std::cout << description_ << "\n";
}

const std::string& Portal::GetNameFrom(const Room* room) const
{
    if(room == parent_) return name_;
    if(room == destination_) return opposite_name_;
    
    return name_;
}

Room* Portal::GetDestinationFrom(const Room* room) const
{
    if(room == parent_) return destination_;
    if(room == destination_) return (Room*) parent_;
    
    return NULL;
}

