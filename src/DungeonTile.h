//
//  DungeonTile.h
//  forogue
//
//  Created by Lasse Carstensen on 14/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__DungeonTile__
#define __forogue__DungeonTile__

#include <iostream>

#include "Tile.h"

using namespace std;

enum class DungeonTileType { Floor, Wall, Outside, Sand, Grass, Water };

class DungeonTile : public Tile
{
public:
    DungeonTile();
    
    string DrawSymbol();
    
    DungeonTileType type;
    
    bool edgeMask;          // Is edge tile?
    
    int visgroup;   // Used for clustering during vis testing
};

#endif /* defined(__forogue__DungeonTile__) */
