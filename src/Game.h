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

// Boost serialization lib
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Character.h"
#include "Entity.h"
#include "Item.h"
#include "World.h"
#include "Dungeon.h"
#include "SpecialWindow.h"
#include "Gui.h"
#include "Visibility.h"
#include "WeaponParser.h"
#include "TileSet.h"
//#include "AStarSearcher.h"

using namespace std;

class Game
{
public:
    Game(){}
    ~Game();
    
    void Init();
    bool MainLoop();
    void Exit();
    
    void Load();
    void Save();
    
    void CharacterCreation();
    
    bool AttemptCharMove(veci rel);
    
private:
    // For serialization
    friend class Savefile;
    friend class boost::serialization::access;
    
    Gui *gui;
    
    bool isInDungeon;           // in dungeon or travelling
    Location *currLocation;     // current location
    World *world;               // Wasteland overworld
    Character *player;          // Player character
    
    // All generated sub-locations
    // May not be generated in detail yet (wait until visit)
    // This excludes the overworld
    vector<Dungeon*> *locations;
    
    // Every entity in current environment excluding player and "dumb" items on the ground (stuff that can only be picked up)
    // Moved to indiv. dungeons
};

#endif /* defined(__forogue__Game__) */
