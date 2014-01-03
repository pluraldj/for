//
//  World.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
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

#ifndef __forogue__World__
#define __forogue__World__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>
#include <fstream>

#include "Location.h"
#include "WorldSpec.h"
#include "Utils.h"
#include "WorldTile.h"

// The overworld wasteland map
class World : public Location
{
public:
    World(WorldSpec spec);
    ~World();
    
    wstring* drawRect(veci upperleft, veci window, bool fow, Visibility *vis);
    
    // Resize world map when player nears an edge of it
    // TODO in a way so the transition is seamless
    // TODO smart reallocing of tile array
    void Resize(veci dir);
    
    WorldTile **tiles;
    
    // Debug printing of map
    void Dump(string path);
    
    Tile *GetTile(int x, int y);
private:
    void Generate(WorldSpec spec);
};

#endif /* defined(__forogue__World__) */
