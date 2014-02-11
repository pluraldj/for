//
//  Junktown.cpp
//  FOR
//
//  Created by Lasse Carstensen on 10/02/14.
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

#include "Junktown.h"

Junktown::Junktown(DungeonSpec spec) : Dungeon(spec)
{
    // Parent constructor has created tiles etc.
    // And called generation code for us
    
    name = "Junktown";
    
    Generate(spec);
    
    InitPathfinding();
}

Junktown::~Junktown()
{
}

void Junktown::Generate(DungeonSpec spec)
{
    // Get handle to RNG
    RNG *rnd = RNG::getInstance();
    
    // Number of tiles around settlement with no buildings
    // These only contain wasteland nature and exit tiles
    int buffer = 10;
    
    // Initially empty ground
    for ( int i=0; i<size.x; i++ )
    {
        for ( int j=0; j<size.y; j++ )
        {
            tiles[i][j].type = DungeonTileType::Sand;
            tiles[i][j].clipMask = true;
        }
    }
    
    // Bounds of walled enclosure
    townmin = veci(buffer,buffer);
    townmax = size - veci(2*buffer,2*buffer);
    
    // Create enclosing wall
    // TODO: More interesting than rectangle
    MakeWalls(townmin, townmax);
    
    // Special entry/exit area, comes first in the list
    // Exceptionally it may go outside into the buffer zon
    // Always in the north for now (TODO: Random placement of entrance
    veci entrymin = townmin+veci(5,-2);
    veci entrysize = veci(8,6);
    veci entrymax = entrymin+entrysize;
    
    DungeonArea da(entrymin,entrysize);
    areas.push_back(da);
    
    // Punch hole in enclosing wall and make entrance structure
    for ( int x=entrymin.x; x<entrymax.x; x++ )
    {
        for ( int y=entrymin.y+1; y<entrymax.y-1; y++ )
        {
            tiles[x][y].type = DungeonTileType::Sand;
            tiles[x][y].clipMask = true;
        }
    }
    
    // Other areas correspond to single buildings
    // Larger buildings can be split into rooms, but still correspond to one area
    // No areas may overlap, and enforce minimum distance between buildings for passage
    int n=1;
    while ( n < spec.numareas )
    {
        int ox = rnd->random_int(0,size.x-1);
        int oy = rnd->random_int(0,size.y-1);
        int sx = rnd->random_int(spec.area_minsize,spec.area_maxsize);
        int sy = rnd->random_int(spec.area_minsize,spec.area_maxsize);
     
        // Going outside map? Discard it
        if ( ox <= buffer || oy <= buffer || ox+sx >= size.x-2*buffer || oy+sy >= size.y-2*buffer )
            continue;
        
        // Does it intersect any previous ones?
        bool intersect = false;
        for ( int i=0; i<n; i++ )
        {
            DungeonArea other = areas[i];
            
            if ( rectIntersect(veci(ox,oy), veci(sx,sy), other.pos, other.size) )
            {
                intersect = true;
                break;
            }
        }
        
        // Add if it does not intersect any previous ones
        if ( !intersect )
        {
            areas.push_back( DungeonArea( veci(ox,oy), veci(sx,sy) ) );
            n++;
        }
    }
    
    // Fill out walls and floors in buildings
    for ( auto it=areas.begin()+1; it!=areas.end(); it++ )
    {
        DungeonArea ar = (*it);
        
        MakeWalls(ar.pos, ar.pos+ar.size);
    }
    
}

veci Junktown::GetPlayerSpawnCoords()
{
    // Outside entrance
    veci entrymin = areas[0].pos;
    veci entrysize = areas[0].size;
    
    return entrymin + veci(entrysize.x/2,0) + veci(0,-1);
}

// Makes 1 tile wide walls around edge of bbox
// You must punch holes in them later yourself
void Junktown::MakeWalls(veci min, veci max)
{
    int x,y;
    
    // North
    y = min.y;
    for ( x=min.x; x<max.x; x++ )
    {
        tiles[x][y].type = DungeonTileType::Wall;
        tiles[x][y].clipMask = false;
    }
    
    // South
    y = max.y-1;
    for ( x=min.x; x<max.x; x++ )
    {
        tiles[x][y].type = DungeonTileType::Wall;
        tiles[x][y].clipMask = false;
    }
    
    // West
    x = min.x;
    for ( y=min.y; y<max.y; y++ )
    {
        tiles[x][y].type = DungeonTileType::Wall;
        tiles[x][y].clipMask = false;
    }
    
    // Easts
    x = max.x-1;
    for ( y=min.y; y<max.y; y++ )
    {
        tiles[x][y].type = DungeonTileType::Wall;
        tiles[x][y].clipMask = false;
    }
}