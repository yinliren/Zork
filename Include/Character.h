//
//  Character.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef Character_h
#define Character_h
#include <string>
#include "GameObject.h"

class Room;
class Item;

class Character : public GameObject {
public:
    Character(const char* name, const char* description, Room* room);
    ~Character();
    
    virtual bool Go(const std::vector<std::string>& args);
    virtual void Look(const std::vector<std::string>& args) const;
    virtual bool Take(const std::vector<std::string>& args);
    virtual bool Drop(const std::vector<std::string>& args);
    virtual void Inventory() const;
    virtual bool Equip(const std::vector<std::string>& args);
    virtual bool UnEquip(const std::vector<std::string>& args);
    virtual bool AutoEquip();
    virtual bool Lock(const std::vector<std::string>& args);
    virtual bool UnLock(const std::vector<std::string>& args);
    virtual void Tick();
    
    virtual bool Attack(const std::vector<std::string>& args);
    virtual int MakeAttack();
    virtual int ReceiveAttack(int damage);
    virtual void Die();
    virtual bool Loot(const std::vector<std::string>& args);
    virtual void Stats() const;
    
    Room* GetRoom() const;
    bool PlayerInRoom() const;
    bool IsAlive() const;
    
    public :
    
    int hit_points_;
    int min_damage_;
    int max_damage_;
    int min_protection_;
    int max_protection_;
    Character* combat_target_;
    Item* weapon_;
    Item* armour_;
};


#endif /* Character_h */
