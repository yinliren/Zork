//
//  Mailbox.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Mailbox_h
#define Mailbox_h
#include "Item.h"
class Key;
class Mailbox : public Item {
public:
    Mailbox(const char* name, const char* description, GameObject* parent, ItemType item_type = COMMON, bool isOpened=false, Key* key=nullptr);
    ~Mailbox();
    
    bool open();
    bool close();
    Key* getKey();
    
private:
    Key* key_;
    bool isOpened_;
    
};

#endif /* Mailbox_h */
