//
//  WorldTile.cpp
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "WorldTile.h"
#include "TileSet.h"

WorldTile::WorldTile() : Tile()
{
    // World tiles are passable unless otherwise set
    clipMask = true;
    
    type = WorldTileType::Dirt;
    canEnter = false;
    known = true;
    elevation = 0.0;
}

wstring WorldTile::DrawSymbol()
{
    // Never been here before?
    if ( !known )
        return L"!";
    
    return TileSet::getInstance()->WorldTileSymbol(type);
}