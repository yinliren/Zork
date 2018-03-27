//
//  GameObject.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include <stdio.h>
#include "GameObject.h"
#include "Globals.h"
#include <iostream>

GameObject::GameObject(const char* name, const char* description, GameObject* parent = NULL) :
name_(name), description_(description), parent_(parent) {
    type_ = GAMEOBJECT;
    if(parent != NULL)
        parent->container_.push_back(this);
}


GameObject::~GameObject() {}


void GameObject::Look() const
{
    std::cout << name_ << "\n";
    std::cout << description_ << "\n";
}


void GameObject::Tick()
{}


void GameObject::ChangeParentTo(GameObject* new_parent)
{
    if(parent_ != NULL)
        parent_->container_.remove(this);
    
    parent_ = new_parent;
    
    if(parent_ != NULL)
        parent_->container_.push_back(this);
}


bool GameObject::Find(GameObject* gameObject) const
{
    for(std::list<GameObject*>::const_iterator it = container_.begin(); it != container_.cend(); ++it) {
        if((*it) == gameObject)
            return true;
    }
    return false;
}


GameObject* GameObject::Find(GameObjectType type) const
{
    for(std::list<GameObject*>::const_iterator it = container_.begin(); it != container_.cend(); ++it) {
        if((*it)->type_ == type)
            return *it;
    }
    return NULL;
}


GameObject* GameObject::Find(const std::string& name, GameObjectType type) const {
    for(std::list<GameObject*>::const_iterator it = container_.begin(); it != container_.cend(); ++it) {
        if((*it)->type_ == type) {
            if(Same((*it)->name_, name))
                return *it;
        }
    }
    return NULL;
}


void GameObject::FindAll(GameObjectType type, std::list<GameObject*>& list_to_fill) const {
    for(std::list<GameObject*>::const_iterator it = container_.begin(); it != container_.cend(); ++it) {
        if((*it)->type_ == type)
            list_to_fill.push_back(*it);
    }
}

