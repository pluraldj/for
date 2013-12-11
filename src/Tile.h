//
//  Tile.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Tile__
#define __forogue__Tile__

#include <iostream>
#include <string>

#include "Visibility.h"

using namespace std;

enum class TileType { Floor, Wall, Outside, Sand, Grass, Water };


class Tile
{
public:
    Tile();
    
    string DrawSymbol();
    
    TileType type;
    bool clipMask;          // true = can move here
    bool edgeMask;          // Is edge tile?
    
    int visgroup;   // Used for clustering during vis testing
};

#endif /* defined(__forogue__Tile__) */
