//
//  DungeonTile.cpp
//  forogue
//
//  Created by Lasse Carstensen on 14/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "DungeonTile.h"
#include "TileSet.h"

DungeonTile::DungeonTile() : Tile()
{
    type = DungeonTileType::Outside;
    edgeMask = false;
}

wstring DungeonTile::DrawSymbol()
{
    return TileSet::getInstance()->DungeonTileSymbol(type);
}