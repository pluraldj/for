//
//  World.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__World__
#define __forogue__World__

#define _XOPEN_SOURCE_EXTENDED

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
