//
//  WorldTile.cpp
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "WorldTile.h"

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
    
    switch ( type )
    {
        // TODO: Colors!
        case WorldTileType::Dirt: return L"å";
        case WorldTileType::Desert: return L"-";
        case WorldTileType::Grass: return L"\"";
        case WorldTileType::Forest: return L"&";
        
        // Don't distinguish between water tiles
        case WorldTileType::Ocean: return L"=";
        case WorldTileType::River: return L"=";
        case WorldTileType::Lake: return L"=";
            
        case WorldTileType::Ruins: return L"#";
            
        case WorldTileType::Hilly: return L"~";
        case WorldTileType::Mountains: return L"^";
        case WorldTileType::SnowyMountains: return L"^";
            
        case WorldTileType::Cave: return L"C";
        case WorldTileType::Traders: return L"M";
        case WorldTileType::Vault: return L"V";
        case WorldTileType::Camp: return L"T";   // Treated like towns
        case WorldTileType::Town: return L"T";
    }
}