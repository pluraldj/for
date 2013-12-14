//
//  Tile.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Tile__
#define __forogue__Tile__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <string>

#include "Visibility.h"

using namespace std;

class Tile
{
public:
    Tile();
    
    virtual string DrawSymbol() = 0;
    
    bool clipMask;          // true = can move here
    
    protected:
};

#endif /* defined(__forogue__Tile__) */
