//
//  Location.h
//  forogue
//
//  Created by Lasse Carstensen on 01/12/13.
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


#ifndef __forogue__Location__
#define __forogue__Location__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

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
    virtual wstring* drawRect(veci upperleft, veci window, bool fow, Visibility *vis) = 0;
    
    // Implemented by children
    // Should return NULL if out of bounds
    virtual Tile *GetTile(int x, int y) = 0;
    
    string name;
    
    veci size;
    
};

#endif /* defined(__forogue__Location__) */
