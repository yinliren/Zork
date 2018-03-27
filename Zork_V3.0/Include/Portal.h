//
//  Portal.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Portal_h
#define Portal_h
#include <string>
#include "GameObject.h"
#include "Room.h"
class Room;

class Portal : public GameObject {
    
public:
    Portal(const char* name, const char* opposite_name, const char* description, Room* origin, Room* destination, bool one_way = false, bool locked=false);
    ~Portal();
    
    void Look() const;
    
    const std::string& GetNameFrom(const Room* room) const;
    Room* GetDestinationFrom(const Room* room) const;
    
    public :
    bool one_way_;
    bool closed_;
    bool locked_;
    std::string opposite_name_;
    Room* destination_;
    GameObject* key_;
    
};
#endif /* Portal_h */
