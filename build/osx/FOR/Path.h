//
//  Path.h
//  FOR
//
//  Created by Lasse Carstensen on 10/01/14.
//  Copyright (c) 2014 Lasse Carstensen. All rights reserved.
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

#ifndef __FOR__Path__
#define __FOR__Path__

#include <iostream>
#include <vector>

#include "Tile.h"
#include "Util.h"

using namespace std;

class GridGraphVertex;
class AStarSearcher;

enum class Direction { Left, Right, Up, Down };

// A planned path through the game world, ie. an ordered list of tiles to visit
// Used by AIs to plan their movement, created by path finding implementation
struct Path
{
public:
    Path();
    ~Path();

    int currIndex;              // Index into array, where we're currently standing
    
    vector<Tile*> path;         // Every tile along the way
    vector<Direction> deltas;    // What direction to move to get to next tile
};

#endif /* defined(__FOR__Path__) */
