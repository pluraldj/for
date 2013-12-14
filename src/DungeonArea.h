//
//  DungeonArea.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__DungeonArea__
#define __forogue__DungeonArea__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

#include "Utils.h"

class Dungeon;

enum class AreaType { Default, Entry, Exit, Creatures, Loot, RareCreatures, RareLoot };

class DungeonArea
{
public:
    DungeonArea(veci _pos, veci _size);
    
    veci pos;
    veci size;
    
    vecd center;
    
    AreaType type;
};

#endif /* defined(__forogue__DungeonArea__) */
