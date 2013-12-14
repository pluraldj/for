//
//  Game.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Game__
#define __forogue__Game__

#include <iostream>
#include <string>

#include <menu.h>

#include "Character.h"
#include "Entity.h"
#include "Item.h"
#include "World.h"
#include "Dungeon.h"
#include "SpecialWindow.h"
#include "Gui.h"
#include "Visibility.h"
#include "WeaponParser.h"

using namespace std;

class Game
{
public:
    static Game &getInstance()
    {
        static Game g;
        return g;
    }
    
    ~Game();
    
    void Init();
    bool MainLoop();
    void Exit();
    
    void CharacterCreation();
    
    bool AttemptCharMove(veci rel);
    
private:
    Game(){}
    
    Gui *gui;
    
    bool isInDungeon;       // in dungeon or travelling
    Dungeon *dungeon;       // current dungeon
    
    World *world;           // Wasrteland overworld
    Character *player;
    
    // Every entity in current environment excluding player and "dumb" items on the ground (stuff that can only be picked up)
    vector<Entity*> *activeEnts;
};

#endif /* defined(__forogue__Game__) */
