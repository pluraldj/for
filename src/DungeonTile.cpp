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

wstring DungeonTile::DrawSymbol()
{
    switch ( type )
    {
        case DungeonTileType::Outside: return L" ";
        case DungeonTileType::Floor: return L".";
        case DungeonTileType::Wall: return L"#";
        case DungeonTileType::Sand: return L"~";
        case DungeonTileType::Grass: return L"\"";
        case DungeonTileType::Water: return L"=";
    }
}