//
//  WorldTile.cpp
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
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
    
    return TileSet::GetInstance()->WorldTileSymbol(type);
}