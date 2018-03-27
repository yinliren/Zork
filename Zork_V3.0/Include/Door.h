//
//  Door.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Door_h
#define Door_h
#include "Portal.h"
#include "Key.h"

class Door : public Portal {
public:
    Door(const char* name, const char* opposite_name, const char* description, Room* origin, Room* destination, bool one_way = true, const size_t id_num=123, bool locked=false);
    ~Door();
    
    bool keyfits(const Key* k) const;
    bool unlockusing(const Key* k);
    bool lockusing(const Key* k);
    bool isLocked();
    
private:
    size_t id_;
    
};

#endif /* Door_h */
