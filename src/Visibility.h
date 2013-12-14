//
//  Visibility.h
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Visibility__
#define __forogue__Visibility__

#define _XOPEN_SOURCE_EXTENDED

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
