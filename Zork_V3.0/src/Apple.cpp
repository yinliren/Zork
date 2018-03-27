//
//  Apple.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/17/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include "Apple.h"

Apple::Apple(const char* name, const char* description, GameObject* parent, ItemType item_type) : Item(name, description, parent, item_type) {
    health_recover = 20;
    item_type_ = HEALTH_EAT;
}

Apple::~Apple() {}
