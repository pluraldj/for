//
//  WorldTile.h
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__WorldTile__
#define __forogue__WorldTile__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

#include "Tile.h"

using namespace std;

enum class WorldTileType { Dirt, Desert, Grass, Forest, Ocean, River, Lake, Ruins, Hilly, Mountains, SnowyMountains, Cave, Camp, Traders, Vault, Town };

class WorldTile : public Tile
{
public:
    WorldTile();
    
    string DrawSymbol();
    
    WorldTileType type;
    bool canEnter;  // Just random wilderness or a place we can go to (enter dungeon)
    
    // Do we know what this place is?
    // When first discovered we must visit it to find out
    // Empty tiles are always known
    bool known;
    
    // heightmap height, related to elevation
    double height;
    
    // Elevation above sea level - negative=below
    double elevation;
};

#endif /* defined(__forogue__WorldTile__) */
