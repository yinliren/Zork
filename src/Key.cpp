//
//  Key.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include "Key.h"

Key::Key(const char* name, const char* description, GameObject* parent, ItemType item_type, const size_t id_num)
: Item(name, description, parent, item_type), keyid_(id_num){
    type_ = ITEM;
    min_value_ = max_value_ = 0;
}
Key::~Key() {}

size_t Key::keyid() const { return keyid_; }
