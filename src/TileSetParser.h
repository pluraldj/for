//
//  TileSetParser.h
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


#ifndef __forogue__TileSetParser__
#define __forogue__TileSetParser__

#define _XOPEN_SOURCE_EXTENDED

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>
#include <vector>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "XmlParser.h"
#include "Tile.h"
#include "DungeonTile.h"
#include "WorldTile.h"
#include "Entity.h"

using namespace std;

class TileSetParser : public XmlParser
{
public:
    TileSetParser();
    ~TileSetParser();
    
    // XML string to tile enum conversion
    DungeonTileType StringToDungeonTileType(string str);
    WorldTileType StringToWorldTileType(string str);
    EntityType StringToEntityType(string str);
    
    TileSet *Load();
    
private:
    
};

#endif /* defined(__forogue__TileSetParser__) */