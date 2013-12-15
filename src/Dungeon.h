//
//  Dungeon.h
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


#ifndef __forogue__Dungeon__
#define __forogue__Dungeon__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <stack>

#include "Tile.h"
#include "Utils.h"
#include "DungeonSpec.h"
#include "DungeonArea.h"
#include "Location.h"
#include "item.h"
#include "Character.h"
#include "Visibility.h"
#include "DungeonTile.h"

using namespace std;

class World;

class Dungeon : public Location
{
public:
    Dungeon(DungeonSpec spec);
    ~Dungeon();
    
    // Draw a rectangular section of the dungeon
    // Done by creating a list of strings each containing one line
    // of symbols to be written to screen
    wstring* drawRect(veci upperleft, veci window, bool fow, Visibility *vis);
    
    // Create passage between areas
    void MakePassage(DungeonArea *A, DungeonArea *B);
    
    // Create passage between tiles (straight-through)
    void MakePassage(vecd A, vecd B);
    
    // Sete edge flags on tiles
    void SetEdgeFlags();
    
    // Create visgroups. Returns number of groups
    int CreateVisGroups();
    
    // Used during vis determination on dungeon creation
    bool recursiveVisFill(int x, int y, int group);
    
    // Get player spawn coords for when we enter the dungeon
    veci GetPlayerSpawnCoords();
    
    // Dump tile map to file
    void Dump(string path);
    
    void DumpVisGroups(string path);
    void DumpEdgeMask(string path);
    
    Tile *GetTile(int x, int y);
    
    // Tiles
    DungeonTile **tiles;
    
    // Areas
    vector<DungeonArea> areas;
    
    // Entities in here
    vector<Entity*> *activeEnts;
    
private:
    // Generate dungeon based on parameters
    void Generate(DungeonSpec spec);
    
    // Populate with objects that can be interacted with
    void SeedWithObjects();
    
    // Populate with enemies/NPCs
    void SeedWithCreatures();
    
    // Populate with loot, both on ground and in containers
    void SeedWithItems();
};

#endif /* defined(__forogue__Dungeon__) */
