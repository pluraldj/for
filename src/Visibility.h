//
//  Visibility.h
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
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


#ifndef __forogue__Visibility__
#define __forogue__Visibility__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>
#include <string>

#include "Utils.h"

class Dungeon;
class World;
class Character;

using namespace std;

enum class VisibilityType { Light, Fow, Dark };

class Visibility
{
public:
    Visibility(Dungeon *_dungeon, Character *_owner);
    Visibility(World *_world, Character *_owner);
    ~Visibility();
    
    // Clear visibility to dark
    void ClearVis();
    
    // Update visibility from point of view of character
    void UpdateVis();
    
    // Only one of these is active
    Dungeon *dungeon;       // Dungeon we're computing vis for
    World *world;
    
    Character *owner;       // Guy who sees this
    veci size;              // Same as dungeon->size
    VisibilityType **tiles; // 2D array of size size
    
private:
    void CastLight(int row, double start, double end, int xx, int xy, int yx, int yy);
    
    void UpdateVisInDungeon();
    void UpdateVisInWorld();
    
    double **lightMap;
};

#endif /* defined(__forogue__Visibility__) */
