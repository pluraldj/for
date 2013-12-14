//
//  TileSet.cpp
//  forogue
//
//  Created by Lasse Carstensen on 14/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "TileSet.h"

void TileSet::LoadFromFile(string path)
{
    //TODO
}

TileSet::~TileSet()
{
}

void TileSet::UseDefault()
{
    worldSymbols.clear();
    dungeonSymbols.clear();
    entitySymbols.clear();
    
    // Initialize everything with default tile symbols
    // WORLD
    worldSymbols[WorldTileType::Dirt] = L".";
    
    // DUNGEON
    
    // STUFF
}

wstring TileSet::WorldTileSymbol(WorldTileType t)
{
    // Attempt lookup
    auto it = worldSymbols.find(t);
    
    // Failed? draw error sign
    // TODO: Maybe signal error to user?
    if ( it == worldSymbols.end() )
        return L"?";
    
    // Else just give it
    return (*it).second;
}

wstring TileSet::DungeonTileSymbol(DungeonTileType t)
{
    // Attempt lookup
    auto it = dungeonSymbols.find(t);
    
    // Failed? draw error sign
    // TODO: Maybe signal error to user?
    if ( it == dungeonSymbols.end() )
        return L"?";
    
    // Else just give it
    return (*it).second;
}

wstring TileSet::EntitySymbol(EntityType t)
{
    // Attempt lookup
    auto it = entitySymbols.find(t);
    
    // Failed? draw error sign
    // TODO: Maybe signal error to user?
    if ( it == entitySymbols.end() )
        return L"?";
    
    // Else just give it
    return (*it).second;
}