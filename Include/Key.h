//
//  Key.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Key_h
#define Key_h
#include "Item.h"
#include "GameObject.h"

class Key : public Item {
public:
    Key(const char* name, const char* description, GameObject* parent, ItemType item_type = COMMON, const size_t id_num=123);
    ~Key();
    size_t keyid() const;
private:
    size_t keyid_;
};

#endif /* Key_h */
