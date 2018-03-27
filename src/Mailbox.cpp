//
//  Mailbox.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Mailbox.h"
Mailbox::Mailbox(const char* name, const char* description, GameObject* parent, ItemType item_type, bool isOpened, Key* key)
: Item(name, description, parent, item_type), isOpened_(isOpened), key_(key) {
    type_ = ITEM;
    min_value_ = max_value_ = 0;
}
Mailbox::~Mailbox() {}


bool Mailbox::open() {
    if (isOpened_) {
        std::cout << "It's already opened.\n";
        return false;
    }
    else {
        isOpened_ = true;
        return true;
    }
}

bool Mailbox::close() {
    if (!isOpened_) {
        std::cout << "It's already closed.\n";
        return false;
    }
    else {
        isOpened_ = false;
        return true;
    }
    
}

Key* Mailbox::getKey() {
    return key_;    
}
