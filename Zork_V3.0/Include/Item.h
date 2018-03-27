//
//  Item.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Item_h
#define Item_h
#include <string>
#include "GameObject.h"

class Room;

enum ItemType {
    COMMON,
    WEAPON,
    ARMOUR,
    HEALTH_EAT,
    HEALTH_DRINK,
    COIN
};

class Item : public GameObject {
public:
    Item(const char* name, const char* description, GameObject* parent, ItemType item_type = COMMON);
    ~Item();
    
    void Look() const;
    int GetValue() const;
    
    public :
    size_t min_value_;
    size_t max_value_;
    ItemType item_type_;
    size_t health_recover_;
};

#endif /* Item_h */
