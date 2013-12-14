//
//  TileSet.h
//  forogue
//
//  Created by Lasse Carstensen on 14/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

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
