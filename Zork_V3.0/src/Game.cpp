//
//  Game.cpp
//  Zork_V3.0
//
//  Created by Liren on 12/16/17.
//  Copyright © 2017 Liren. All rights reserved.
//

#include "Game.h"
#include <iostream>
#include "Globals.h"
#include "GameObject.h"
#include "Character.h"
#include "Item.h"
#include "Portal.h"
#include "Room.h"
#include "Player.h"
#include "Game.h"
#include "Key.h"
#include "Mailbox.h"
#include "Door.h"
#include "Monster.h"

Game::Game()
{
    tick_timer_ = clock();
    // Rooms ----
    Room* forest1 = new Room("Forest", "You are surrounded by tall trees, and it's very easy to get lost in here, but you see a wooden room on south.");
    Room* woodenHouse = new Room("WoodenHouse", "It's a small wooden house and the door is not locked.");
    Room* woods = new Room("Woods", "There're some trees in this area, and you see a fierce wolve standing in the middle.");
    Room* weaponRoom = new Room("WeaponRoom", "It's a weapon room hinding in the forest, but the door is locked.");
    Room* forest3 = new Room("Forest", "It's another forest and you are surrounded by tall trees. There's a cave on west side, and you can hear something is roaring.");
    Room* dragonCave = new Room("Cave", "You see a giant dragon breathing in fire!!!");
    Room* forest2 = new Room("Forest","It's another forest and you are surrounded by tall trees, but you see lights toward north side.");
    Room* forest4 = new Room("Forest", "It's another forest and you are surrounded by tall trees. You see lights toward north and east side.");
    Room* cliffEdge = new Room("CliffEdge", "It's a cliff edge. the only exit is south. But  you could try go north to see what happen.");
    Room* cliffBottom1 = new Room("CliffBottom", "High cliff bottom.");
    Room* cliffBottom2 = new Room("CliffBottom", "Extremely high cliff bottom.");
    Room* emptyGround = new Room("EmptyGround", "Empty ground. You see a well on east. There is a whole on the ground");
    Room* underGround = new Room("underGround", "Try to find something in here.");
    Room* bushes = new Room("Bushes", "Nothins is here but bushes.");
    Room* woods1 = new Room("Woods", "Try find something in here.");
    Room* woods2 = new Room("Woods", "Nothing else but woods");
    Room* well = new Room("Well", "DEEP Water in well");
    Room* ground = new Room("Ground", "Try to find something in here.");
    Room* grass = new Room("Grass", "A grass ground");
    Room* littleForest = new Room("LittleForest", "It's a small area forest.");
    Room* ground2 = new Room("Ground", "You may need to get a fight here.");
    Room* emptyGround2 = new Room("EmptyGround", "You see a tall building on north.");
    Room* dessert = new Room("Dessert", "Hot and Dry dessert.");
    Room* dessert2 = new Room("Dessert", "Dangerous and hot dessert.");
    Room* dessert3 = new Room("Dessert", "Dessert with hope.");
    Room* Castle = new Room("WhiteCastle", "A beautiful and properous Castle with Happy People");
    
    
    
    //--------------------Portals--------------------------------
    //weaponRoom at south, woods at north
    Door* weaponRoomDoor = new Door("south", "north", "IronGate", woods, weaponRoom, false, 123);
    weaponRoomDoor->locked_ = true;
    
    
    
    Portal* path_woodenHouse_woods = new Portal("north", "south", "Little Path", woods, woodenHouse);//woods at south, woodenHouse at north
    
    
    Portal* path_Forest1_woodenHouse = new Portal("south", "north", "Wide Path", forest1, woodenHouse);// woodenHouse at south, forest1 at north
    
    
    Portal* path_Forest1_Forest2 = new Portal("north", "south", "Faded Path in Forest", forest1, forest2); // forest1 at south, forest2 at north
    
    
    Portal* path_Forest1_Forest3 = new Portal("west", "east", "Faded Path in Forest", forest1, forest3);// Check, forest1 at east, forest3 at west
    
    
    Portal* path_forest1_Forest4 = new Portal("east" ,"west", "Small path in forest", forest1, forest4);//Check, forest1 at west, forest4 at east
    
    Portal* path_forest3_DragonCave = new Portal("west", "east", "Small Path to a Cave", forest3, dragonCave);//Check, forest3 at east, DragonCave at west
    
    Portal* path_forest4_Grass = new Portal("north", "south", "A normal path", forest4, grass);//Check, forest4 at south, grass at north
    
    Portal* path_grass_littleForest = new Portal("east", "west", "a path to little forest", grass, littleForest);//grass at west, lille forest at east
    
    
    Portal* path_forest4_cliffEdge = new Portal("east", "west", "a path to cliff edge", forest4, cliffEdge);//Check, forest4 at west, CliffEdge at east
    
    Portal* path_cliffEdge_cliffBottom1 = new Portal("north", "south", "Cannot see what's there", cliffEdge, cliffBottom1);//cliffEdge at south, Cliff Bottom1 at north
    
    Portal* path_cliffEdge_cliffBorrom2 = new Portal("east", "west", "Cannot see what's there", cliffEdge, cliffBottom2);// CliffEdge at west, CliffBottom2 at east
    
    
    Portal* path_cliffEdge_EmptyGround = new Portal("south", "north", "a wide path", cliffEdge, emptyGround);//cliffEdge at north, emptyGround at south
    
    Portal* path_EmptyGround_Bushes = new Portal("south", "north", "a small path", emptyGround, bushes);//emptyGround at north, bushes at south
    
    Portal* path_woods1_bushes = new Portal("east", "west", "a hidden path", woods1, bushes);
    
    
    Portal* path_woods1_woods2 = new Portal("north", "south", "a hidden path", woods1, woods2);
    
    
    Portal* path_woods2_EmptyGround = new Portal("east", "west", "a hidden path", woods2, emptyGround);
    
    
    Portal* path_EmptyGround_Well = new Portal("east", "west", "a narrow path", emptyGround, well);
    
    
    Portal* path_EmptyGround_underGround = new Portal("down", "up", "a pipe in the ground", emptyGround, underGround);
    
    
    Portal* path_forest2_dessert = new Portal("north", "south", "a path", forest2, dessert);
    
    
    Portal* path_dessert_dessert2 = new Portal("west", "east", "a path covered by sands", dessert, dessert2);
    
    
    Portal* path_dessert2_dessert3 = new Portal("east", "west", "a path cannot be seen because is in dessert", dessert3, dessert2);
    
    
    Portal* path_dessert_EmptyGround2 = new Portal("east", "west", "a path between dessert and empty ground", dessert, emptyGround2);
    
    
    Portal* path_emptyGround2_Ground2 = new Portal("east", "west", "a path on the ground", emptyGround2, ground2);
    
    
    Portal* path_ground2_littleForest = new Portal("north", "south", "a path between little forest and an open space", littleForest, ground2);
    
    Portal* path_bushes_Ground = new Portal("east", "west", "A wide path", bushes, ground);
    Portal* path_EmptyGround2_Castle = new Portal("south", "north", "A flat, wide, shiny path with Flowers", Castle, emptyGround2);
    
    gameObject_.push_back(forest1);
    gameObject_.push_back(woodenHouse);
    gameObject_.push_back(woods);
    gameObject_.push_back(weaponRoom);
    gameObject_.push_back(forest3);
    gameObject_.push_back(dragonCave);
    gameObject_.push_back(forest2);
    gameObject_.push_back(forest4);
    gameObject_.push_back(cliffEdge);
    gameObject_.push_back(cliffBottom1);
    gameObject_.push_back(cliffBottom2);
    gameObject_.push_back(emptyGround);
    gameObject_.push_back(underGround);
    gameObject_.push_back(bushes);
    gameObject_.push_back(woods1);
    gameObject_.push_back(woods2);
    gameObject_.push_back(well);
    gameObject_.push_back(ground);
    gameObject_.push_back(grass);
    gameObject_.push_back(littleForest);
    gameObject_.push_back(ground2);
    gameObject_.push_back(emptyGround2);
    gameObject_.push_back(dessert);
    gameObject_.push_back(dessert2);
    gameObject_.push_back(dessert3);


    gameObject_.push_back(weaponRoomDoor);
    gameObject_.push_back(path_woodenHouse_woods);
    gameObject_.push_back(path_Forest1_woodenHouse);
    gameObject_.push_back(path_Forest1_Forest2);
    gameObject_.push_back(path_Forest1_Forest3);
    gameObject_.push_back(path_forest3_DragonCave);
    gameObject_.push_back(path_forest1_Forest4);
    gameObject_.push_back(path_forest4_Grass);
    gameObject_.push_back(path_grass_littleForest);
    gameObject_.push_back(path_forest4_cliffEdge);
    gameObject_.push_back(path_cliffEdge_cliffBottom1);
    gameObject_.push_back(path_cliffEdge_cliffBorrom2);
    gameObject_.push_back(path_cliffEdge_EmptyGround);
    gameObject_.push_back(path_EmptyGround_Bushes);
    gameObject_.push_back(path_woods1_bushes);
    gameObject_.push_back(path_EmptyGround_Well);
    gameObject_.push_back(path_EmptyGround_underGround);
    gameObject_.push_back(path_forest2_dessert);
    gameObject_.push_back(path_dessert_dessert2);
    gameObject_.push_back(path_dessert2_dessert3);
    gameObject_.push_back(path_dessert_EmptyGround2);
    gameObject_.push_back(path_emptyGround2_Ground2);
    gameObject_.push_back(path_ground2_littleForest);
    gameObject_.push_back(path_woods1_woods2);
    gameObject_.push_back(path_woods2_EmptyGround);
    gameObject_.push_back(path_bushes_Ground);
    gameObject_.push_back(path_EmptyGround2_Castle);

    // Characters ----
    Character* Thief = new Character("Thief", "A thief who is holding something", woodenHouse);
    Thief->hit_points_ = 5;
    Thief->max_damage_ = 2;
    Thief->min_damage_ = 1;
    gameObject_.push_back(Thief);
    
    Character* GiantDragon = new Character("GiantDragon", "A Giant Dragon who is breathing in fire~~~", dragonCave);
    GiantDragon->type_ = MONSTER;
    GiantDragon->hit_points_ = 200;
    GiantDragon->max_damage_ = 25;
    GiantDragon->min_damage_ = 20;
    GiantDragon->min_protection_ = 10;
    GiantDragon->max_protection_ = 15;
    gameObject_.push_back(GiantDragon);
    
    Character* DemonHunter1 = new Character("DemonHunter", "Demon Hunter who is hunting for Heros", grass);
    DemonHunter1->hit_points_ = 30;
    DemonHunter1->min_damage_ = 8;
    DemonHunter1->max_damage_ = 10;
    DemonHunter1->min_protection_ = 8;
    DemonHunter1->max_protection_ = 12;
    gameObject_.push_back(DemonHunter1);
    
    Character* DemonHunter2 = new Character("DemonHunter", "Demon Hunter who is hunting for Heros", ground2);
    DemonHunter2->hit_points_ = 30;
    DemonHunter2->min_damage_ = 8;
    DemonHunter2->max_damage_ = 10;
    DemonHunter2->min_protection_ = 8;
    DemonHunter2->max_protection_ = 12;
    gameObject_.push_back(DemonHunter2);
    
    Monster* littleDragon = new Monster("LittleDragon", "A small dragon with sharp claws and teeth", dessert2);
    littleDragon->hit_points_ = 15;
    littleDragon->min_damage_ = 4;
    littleDragon->max_damage_ = 6;
    littleDragon->min_protection_ = 6;
    littleDragon->max_protection_ = 8;
    gameObject_.push_back(littleDragon);
    
    Monster* littleDragon2 = new Monster("LittleDragon", "A small dragon with sharp claws and teeth", woods);
    littleDragon2->hit_points_ = 10;
    littleDragon2->min_damage_ = 2;
    littleDragon2->max_damage_ = 3;
    littleDragon2->min_protection_ = 1;
    littleDragon2->max_protection_ = 2;
    gameObject_.push_back(littleDragon2);
    
    // Items -----
    Item* IronShield = new Item("IronShield", "An Iron Shield", weaponRoom, ARMOUR);
    IronShield->min_value_ = 10;
    IronShield->max_value_ = 20;
    gameObject_.push_back(IronShield);
    
    Item* IronSword = new Item("IronSword", "An Iron Sword", weaponRoom, WEAPON);
    IronSword->min_value_ = 20;
    IronSword->max_value_ = 25;
    gameObject_.push_back(IronSword);
    
    Key* weaponRoom_Key = new Key("WeaponRoomKey", "Iron Key", littleDragon2, COMMON, 88888888);
    weaponRoomDoor->key_ = weaponRoom_Key;
    gameObject_.push_back(weaponRoom_Key);
    
    Item* apple = new Item("apple", "An apple can retore hit_point", Thief, HEALTH_EAT);
    apple->health_recover_ = 10;
    gameObject_.push_back(apple);
    
    Item* Knive = new Item("Knive", "A small Knive", Thief, WEAPON);
    Knive->min_value_ = 8;
    Knive->max_value_ = 11;
    gameObject_.push_back(Knive);
    
    Item* HeroShield = new Item("HeroShield", "A GOLDEN Shield for Absolute Hero", underGround, ARMOUR);
    HeroShield->min_value_ = 90;
    HeroShield->max_value_ = 100;
    gameObject_.push_back(HeroShield);
    
    Item* HeroSword = new Item("HeroSword", "A GOLDEN Sword for Absolute Hero", ground, WEAPON);
    HeroSword->min_value_ = 90;
    HeroSword->max_value_ = 100;
    gameObject_.push_back(HeroSword);
    
    Item* EnergyDrink = new Item("EnergyDrink", "Energy Drink can restore great deal of hit points", dessert3, HEALTH_DRINK);
    EnergyDrink->health_recover_ = 45;
    gameObject_.push_back(EnergyDrink);
    
    // Player ----
    player_ = new Player("Hero", "You are an awesome adventurer!", forest1);
    player_->hit_points_ = 20;
    player_->max_damage_ = 5;
    player_->min_damage_ = 2;
    gameObject_.push_back(player_);
    Thief->combat_target_ = player_;
    GiantDragon->combat_target_ = player_;
    DemonHunter1->combat_target_ = player_;
    DemonHunter2->combat_target_ = player_;
    littleDragon->combat_target_ = player_;
    littleDragon2->combat_target_ = player_;
}


Game::~Game() {
    for(std::list<GameObject*>::iterator it = gameObject_.begin(); it != gameObject_.end(); ++it)
        delete *it;
    
    gameObject_.clear();
}


bool Game::Tick(std::vector<std::string>& args) {
    bool ret = true;
    if(args.size() > 0 && args[0].length() > 0)
        ret = Parser(args);
    GameLoop();
    return ret;
}


void Game::GameLoop() {
    clock_t now = clock();
    if((now - tick_timer_) / CLOCKS_PER_SEC > TICK_FREQUENCY)
    {
        for(std::list<GameObject*>::iterator it = gameObject_.begin(); it != gameObject_.end(); ++it)
            (*it)->Tick();
        tick_timer_ = now;
    }
}


bool Game::Parser(std::vector<std::string>& args) {
    bool ret = true;
    
    switch(args.size()) {
        // commands with no arguments ------------------------------
        case 1:
        {
            if(Same(args[0], "look") || Same(args[0], "l")) {
                player_->Look(args);
            }
            else if(Same(args[0], "north") || Same(args[0], "n") || Same(args[0], "North")
                    || Same(args[0], "NORTH")) {
                if (args.size() == 1)args.push_back("north");
                else args[1] = "north";
                player_->Go(args);
            }
            else if(Same(args[0], "south") || Same(args[0], "s") || Same(args[0], "South")
                    || Same(args[0], "SOUTH")) {
                if (args.size() == 1) args.push_back("south");
                else args[1] = "south";
                player_->Go(args);
            }
            else if(Same(args[0], "east") || Same(args[0], "e") || Same(args[0], "East")
                    || Same(args[0], "EAST")) {
                if (args.size() == 1) args.push_back("east");
                else args[1] = "east";
                player_->Go(args);
            }
            else if(Same(args[0], "west") || Same(args[0], "w") || Same(args[0], "North")
                    || Same(args[0], "NORTH")) {
                if (args.size() == 1) args.push_back("west");
                else args[1] = "west";
                player_->Go(args);
            }
            else if(Same(args[0], "up") || Same(args[0], "u") || Same(args[0], "U")
                    || Same(args[0], "UP") || Same(args[0], "Up")) {
                if (args.size() == 1) args.push_back("up");
                else args[1] = "up";
                player_->Go(args);
            }
            else if(Same(args[0], "down") || Same(args[0], "d") || Same(args[0], "Down")
                    || Same(args[0], "D") || Same(args[0], "Down")) {
                if (args.size() == 1) args.push_back("down");
                else args[1] = "down";
                player_->Go(args);
            }
            else if(Same(args[0], "stats") || Same(args[0], "st") || Same(args[0], "Stats")
                    || Same(args[0], "STATS")) {
                player_->Stats();
            }
            else if(Same(args[0], "inventory") || Same(args[0], "i") || Same(args[0], "INVENTORY")
                    || Same(args[0], "Inven") || Same(args[0], "Inventory")) {
                player_->Inventory();
            }
            else
                ret = false;
            break;
        }
            
        // commands with one argument ------------------------------
        case 2:
        {
            if(Same(args[0], "look") || Same(args[0], "l") || Same(args[0], "Look") || Same(args[0], "LOOK")) {
                player_->Look(args);
            }
            else if(Same(args[0], "go") || Same(args[0], "Go") || Same(args[0], "GO")) {
                player_->Go(args);
            }
            else if(Same(args[0], "take") || Same(args[0], "pick") || Same(args[0], "get") || Same(args[0], "Get")
                    || Same(args[0], "Pick") || Same(args[0], "Take")) {
                player_->Take(args);
            }
            else if(Same(args[0], "drop") || Same(args[0], "put") || Same(args[0], "disregard")
                    || Same(args[0], "Drop") || Same(args[0], "DROP")) {
                player_->Drop(args);
            }
            else if(Same(args[0], "equip") || Same(args[0], "eq") || Same(args[0], "wear") || Same(args[0], "hold")) {
                player_->Equip(args);
            }
            else if(Same(args[0], "unequip") || Same(args[0], "uneq")) {
                player_->UnEquip(args);
            }
            else if(Same(args[0], "examine") || Same(args[0], "ex")) {
                player_->Examine(args);
            }
            else if(Same(args[0], "attack") || Same(args[0], "at") || Same(args[0], "fire") || Same(args[0], "shoot")) {
                player_->Attack(args);
            }
            else if(Same(args[0], "loot") || Same(args[0], "lt")) {
                player_->Loot(args);
            }
            else if(Same(args[0], "eat") || Same(args[0], "Eat") || Same(args[0], "EAT") || Same(args[0], "ate")
                    || Same(args[0], "drink") || Same(args[0], "Drink") || Same(args[0], "DRINK")) {
                player_->Eat(args);
            }
            else
                ret = false;
            break;
        }
            
        // commands with two arguments ------------------------------
        case 3:
        {
            break;
        }
            
        // commands with three arguments ------------------------------
        case 4:
        {
            if(Same(args[0], "unlock") || Same(args[0], "unlk") || Same(args[0], "Unlock")
               || Same(args[0], "UNLOCK")) {
                player_->UnLock(args);
            }
            else if(Same(args[0], "lock") || Same(args[0], "lk") || Same(args[0], "Lock")
                    || Same(args[0], "LOCK")) {
                player_->Lock(args);
            }
            else if(Same(args[0], "take") || Same(args[0], "pick")) {
                player_->Take(args);
            }
            else if(Same(args[0], "drop") || Same(args[0], "put")) {
                player_->Drop(args);
            }
            else
                ret = false;
            break;
        }
        default:
            ret =  false;
    }
    
    return ret;
}

