//
//  Location.h
//  forogue
//
//  Created by Lasse Carstensen on 01/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Location__
#define __forogue__Location__

#include <iostream>
#include <string>

#include "Utils.h"
#include "Visibility.h"
#include "Tile.h"

using namespace std;

class Location
{
public:
    Location()
    {
        // Override these in derived classes
        name = "Location";
        size = veci(0,0);
    }
    
    // Children must override and implement own drawing
    virtual string* drawRect(veci upperleft, veci window, bool fow, Visibility *vis) = 0;
    
    // Implemented by children
    // Should return NULL if out of bounds
    virtual Tile *GetTile(int x, int y) = 0;
    
    string name;
    
    veci size;
    
};

#endif /* defined(__forogue__Location__) */
