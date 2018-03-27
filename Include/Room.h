//
//  Room.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Room_h
#define Room_h
#include <string>
#include <list>
#include "GameObject.h"

class Portal;
class Item;

class Room : public GameObject {
public:
    Room(const char* name, const char* description);
    ~Room();
    
    void Look() const;
    
    Portal* GetPortal(const std::string& direction) const;
    
    public :
};



#endif /* Room_h */
