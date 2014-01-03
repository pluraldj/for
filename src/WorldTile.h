//
//  WorldTile.h
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
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


#ifndef __forogue__WorldTile__
#define __forogue__WorldTile__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>

#include "Tile.h"

using namespace std;

enum class WorldTileType { Dirt, Desert, Grass, Forest, Ocean, River, Lake, Ruins, Hilly, Mountains, SnowyMountains, Cave, Camp, Traders, Vault, Town };

class WorldTile : public Tile
{
public:
    WorldTile();
    
    wstring DrawSymbol();
    
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
