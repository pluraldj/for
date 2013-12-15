//
//  TileSet.h
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


#ifndef __forogue__TileSet__
#define __forogue__TileSet__

#include <iostream>
#include <string>
#include <map>

#include "WorldTile.h"
#include "DungeonTile.h"
#include "Entity.h"

using namespace std;

// A collection of symbols assigned to different stuff for drawing
class TileSet
{
public:
    static TileSet *getInstance(){ static TileSet s; return &s; }
    ~TileSet();
    
    void LoadFromFile(string path);
    
    wstring WorldTileSymbol(WorldTileType t);
    wstring DungeonTileSymbol(DungeonTileType t);
    wstring EntitySymbol(EntityType t);
    
private:
    TileSet() { UseDefault(); }
    void UseDefault();
    
    map<WorldTileType,wstring> worldSymbols;
    map<DungeonTileType,wstring> dungeonSymbols;
    map<EntityType,wstring> entitySymbols;
};


#endif /* defined(__forogue__TileSet__) */
