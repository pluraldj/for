//
//  Dungeon.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Dungeon__
#define __forogue__Dungeon__

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
    string* drawRect(veci upperleft, veci window, bool fow, Visibility *vis);
    
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
    
    // Tiles
    veci size;
    Tile **tiles;
    
    // Areas
    vector<DungeonArea> areas;
    
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
