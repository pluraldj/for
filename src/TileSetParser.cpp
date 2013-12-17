//
//  TileSetParser.cpp
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


#include "TileSetParser.h"
#include "TileSet.h"

TileSetParser::TileSetParser()
{
}

TileSetParser::~TileSetParser()
{
}

DungeonTileType TileSetParser::StringToDungeonTileType(string str)
{
    if ( str == "outside" )
        return DungeonTileType::Outside;
    else if ( str == "floor" )
        return DungeonTileType::Floor;
    else if ( str == "wall" )
        return DungeonTileType::Wall;
    else if ( str == "sand" )
        return DungeonTileType::Sand;
    else if ( str == "grass" )
        return DungeonTileType::Grass;
    else if ( str == "water" )
        return DungeonTileType::Water;
    else
    {
        throw "Unrecognized dungeon tile string " + str;
        return DungeonTileType::Floor;
    }
}

WorldTileType TileSetParser::StringToWorldTileType(string str)
{
    if ( str == "dirt" )
        return WorldTileType::Dirt;
    else if ( str == "desert" )
        return WorldTileType::Desert;
    else if ( str == "grass" )
        return WorldTileType::Grass;
    else if ( str == "forest" )
        return WorldTileType::Forest;
    else if ( str == "ocean" )
        return WorldTileType::Ocean;
    else if ( str == "river" )
        return WorldTileType::River;
    else if ( str == "lake" )
        return WorldTileType::Lake;
    else if ( str == "ruins" )
        return WorldTileType::Ruins;
    else if ( str == "hilly" )
        return WorldTileType::Hilly;
    else if ( str == "mountains" )
        return WorldTileType::Mountains;
    else if ( str == "snowymountains" )
        return WorldTileType::SnowyMountains;
    else if ( str == "cave" )
        return WorldTileType::Cave;
    else if ( str == "traders" )
        return WorldTileType::Traders;
    else if ( str == "vault" )
        return WorldTileType::Vault;
    else if ( str == "camp" )
        return WorldTileType::Camp;
    else if ( str == "town" )
        return WorldTileType::Town;
    else
    {
        throw "Unrecognized world tile string " + str;
        return WorldTileType::Dirt;
    }
}

EntityType TileSetParser::StringToEntityType(string str)
{

    // TODO
    
    return EntityType::Player;
    
}

TileSet *TileSetParser::Load()
{
    // Dummy values to start with
    TileSet *result = new TileSet();
    
    // We want the default key/value pairs in the hashmaps as we're just overwriting any defined in XML
    // This way we keep default tiles for any not specified
    
    
    return result;
}