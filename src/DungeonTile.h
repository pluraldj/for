//
//  DungeonTile.h
//  forogue
//
//  Created by Lasse Carstensen on 14/12/13.
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


#ifndef __forogue__DungeonTile__
#define __forogue__DungeonTile__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

#include "Tile.h"

using namespace std;

enum class DungeonTileType { Floor, Wall, Outside, Sand, Grass, Water };

class DungeonTile : public Tile
{
public:
    DungeonTile();
    
    wstring DrawSymbol();
    
    DungeonTileType type;
    
    bool edgeMask;          // Is edge tile?
    
    int visgroup;   // Used for clustering during vis testing
};

#endif /* defined(__forogue__DungeonTile__) */
