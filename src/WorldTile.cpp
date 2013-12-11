//
//  WorldTile.cpp
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "WorldTile.h"

WorldTile::WorldTile()
{
    type = WorldTileType::Ground;
    visible = false;
    canEnter = false;
    known = true;
    elevation = 0.0;
}

string WorldTile::DrawSymbol()
{
    // Never been here before?
    if ( !known )
        return "!";
    
    switch ( type )
    {
        // TODO: Colors!
        case WorldTileType::Ground: return ".";
        case WorldTileType::Desert: return "~";
        case WorldTileType::Grass: return "\"";
        case WorldTileType::River: return "=";
        case WorldTileType::Lake: return "=";
        case WorldTileType::Ruins: return "#";
        case WorldTileType::Hilly: return "^";
        case WorldTileType::Mountains: return "^";
        case WorldTileType::Cave: return "C";
        case WorldTileType::Traders: return "M";
        case WorldTileType::Vault: return "V";
        case WorldTileType::Camp: return "T";   // Treated like towns
        case WorldTileType::Town: return "T";
    }
}