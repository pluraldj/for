//
//  Game.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//
// This file is part of FOR.
//
// FOR is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// FOR is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FOR (see file LICENSE).  If not, see <http://www.gnu.org/licenses/>.


#ifndef __forogue__Game__
#define __forogue__Game__

#define _XOPEN_SOURCE_EXTENDED

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
    Location *location;       // current location
    
    World *world;           // Wasteland overworld
    Character *player;
    
    // Every entity in current environment excluding player and "dumb" items on the ground (stuff that can only be picked up)
    vector<Entity*> *activeEnts;
};

#endif /* defined(__forogue__Game__) */
