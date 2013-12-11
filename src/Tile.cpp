//
//  Tile.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Tile.h"

Tile::Tile()
{
    type = Outside;
    clipMask = false;
    edgeMask = false;
}

string Tile::DrawSymbol()
{
    switch ( type )
    {
        case TileType::Outside: return " ";
        case TileType::Floor: return ".";
        case TileType::Wall: return "#";
        case TileType::Sand: return "~";
        case TileType::Grass: return "\"";
        case TileType::Water: return "=";
    }
    
    return " ";
}