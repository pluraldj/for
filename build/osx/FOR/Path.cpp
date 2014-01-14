//
//  Path.cpp
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

#include "Path.h"

#include "AStarSearcher.h"

Path::Path()
{
    currIndex = 0;
    
    path = new vector<Tile*>;
    deltas = new vector<PathDirection>;
    
    active = false;
}

// Construct path from list of GridGraphVertex objects as returned by A* impl.
// Using also the Tile* list in a map
Path::Path(vector<GridGraphVertex*> *verts, Location *loc)
{
    Path(); // reset and std. init
    
    // Set Tile* ordering
    for ( auto it=verts->begin(); it != verts->end(); ++it )
    {
        int x = (*it)->coord.x;
        int y = (*it)->coord.y;
        
        Tile *tile = loc->GetTile(x, y);
        
        path->push_back(tile);
    }
    
    // Set relative directions
    for ( auto it=verts->begin(); it != verts->end() - 1; ++it )
    {
        // Coords of this and next
        veci cthis = (*it)->coord;
        veci cnext = (*(it+1))->coord;
        
        // Coord difference
        veci delta = cnext - cthis;
        
        // Figure out direction from delta
        PathDirection dir;
        if ( delta.x == 1 && delta.y == 0 )
            dir = PathDirection::Right;
        else if ( delta.x == -1 && delta.y == 0 )
            dir = PathDirection::Left;
        else if ( delta.x == 0 && delta.y == 1 )
            dir = PathDirection::Down;
        else if ( delta.x == 0 && delta.y == -1 )
            dir = PathDirection::Up;
        else
        {
            dir = PathDirection::None;
            throw new std::runtime_error("Path not connected");
        }
        
        deltas->push_back(dir);
    }
    
    // For final step, there's nowhere to go
    deltas->push_back(PathDirection::None);
}

Path::~Path()
{
    if ( path )
        delete path;
    
    if ( deltas )
        delete deltas;
}

Tile *Path::GetCurrentTile()
{
    return path->at(currIndex);
}

PathDirection Path::GetCurrentDir()
{
    return deltas->at(currIndex);
}

void Path::Advance()
{
    currIndex++;
    
    if ( currIndex >= path->size() )
        throw new std::runtime_error("Path index exceeds path length");
}