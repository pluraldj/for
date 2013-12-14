//
//  DungeonTile.cpp
//  forogue
//
//  Created by Lasse Carstensen on 14/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "DungeonTile.h"

DungeonTile::DungeonTile() : Tile()
{
    type = DungeonTileType::Outside;
    edgeMask = false;
}

string DungeonTile::DrawSymbol()
{
    switch ( type )
    {
        case DungeonTileType::Outside: return " ";
        case DungeonTileType::Floor: return ".";
        case DungeonTileType::Wall: return "#";
        case DungeonTileType::Sand: return "~";
        case DungeonTileType::Grass: return "\"";
        case DungeonTileType::Water: return "=";
    }
    
    return " ";
}