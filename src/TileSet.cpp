//
//  TileSet.cpp
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


#include "TileSet.h"

TileSet *TileSet::ts = NULL;

void TileSet::LoadFromFile(string path)
{
    // Attempt load from XML
    TileSetParser *tp = new TileSetParser();
    
    // New tile set
    TileSet *newTileSet = tp->Load();
    
    // Delete old
    delete this;
    
    // Set static pointer to new one
    SetInstance(newTileSet);
    
    // Clean up parser object
    delete tp;
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
    worldSymbols[WorldTileType::Desert] = L"-";
    worldSymbols[WorldTileType::Grass] = L",";
    worldSymbols[WorldTileType::Forest] = L"φ";
    worldSymbols[WorldTileType::Ocean] = L"≈";
    worldSymbols[WorldTileType::River] = L"≈";
    worldSymbols[WorldTileType::Lake] = L"≈";
    worldSymbols[WorldTileType::Ruins] = L"#";
    worldSymbols[WorldTileType::Hilly] = L"~";
    worldSymbols[WorldTileType::Mountains] = L"^";
    worldSymbols[WorldTileType::SnowyMountains] = L"^";
    
    // DUNGEON
    dungeonSymbols[DungeonTileType::Outside] = L" ";
    dungeonSymbols[DungeonTileType::Floor] = L".";
    dungeonSymbols[DungeonTileType::Wall] = L"#";
    dungeonSymbols[DungeonTileType::Sand] = L"~";
    dungeonSymbols[DungeonTileType::Grass] = L",";
    dungeonSymbols[DungeonTileType::Water] = L"≈";
    
    // STUFF
    entitySymbols[EntityType::Player] = L"@";
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