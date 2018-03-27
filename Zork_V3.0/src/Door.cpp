//
//  Door.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include "Door.h"

class Room;
Door::Door(const char* name, const char* opposite_name, const char* description, Room* origin, Room* destination, bool one_way, const size_t id_num, bool locked) : Portal(name, opposite_name, description, origin, destination, one_way, locked), id_(id_num){
    type_ = PORTAL;
    
    if(one_way == false)
        destination_->container_.push_back(this);
}
Door::~Door() {}

bool Door::keyfits(const Key* k) const {
    return k->keyid() == id_;
}
bool Door::unlockusing(const Key* k) {
    if (keyfits(k)) {
        locked_ = false;
        return true;
    }
    else return false;
}
bool Door::lockusing(const Key* k) {
    if (keyfits(k)) {
        locked_ = true;
        return true;
    }
    else return false;
}

bool Door::isLocked() {
    return locked_;
}
