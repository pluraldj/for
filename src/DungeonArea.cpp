//
//  DungeonArea.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "DungeonArea.h"

DungeonArea::DungeonArea(veci _pos, veci _size)
{
    pos = _pos;
    size = _size;
    
    center = vecd((double)pos.x,(double)pos.y) + 0.5*vecd((double)size.x, (double)size.y);
}