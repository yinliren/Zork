//
//  Apple.h
//  Zork_V3.0
//
//  Created by Liren on 12/17/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Apple_h
#define Apple_h
#include "Item.h"

class Apple : public Item {
public:
    Apple(const char* name, const char* description, GameObject* parent, ItemType item_type = COMMON);
    ~Apple();
    
public:
    size_t health_recover;
};


#endif /* Apple_h */
