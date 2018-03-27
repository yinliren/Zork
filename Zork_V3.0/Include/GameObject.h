//
//  GameObject.h
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h
#include <string>
#include <list>

enum GameObjectType {
    GAMEOBJECT,
    ROOM,
    PORTAL,
    ITEM,
    CHARACTER,
    MONSTER,
    PLAYER
};

class GameObject {
public:
    GameObject(const char* name, const char* description, GameObject* parent);
    virtual ~GameObject();
    
    virtual void Look() const;
    virtual void Tick();
    
    void    ChangeParentTo(GameObject* new_parent);
    bool    Find(GameObject* gameObject) const;
    GameObject* Find(GameObjectType type) const;
    GameObject* Find(const std::string& name, GameObjectType type) const;
    void    FindAll(GameObjectType type, std::list<GameObject*>& list_to_fill) const;
    
    public :
    GameObjectType type_;
    std::string name_;
    std::string description_;
    
    GameObject* parent_;
    std::list<GameObject*> container_;
};


#endif /* GameObject_h */
