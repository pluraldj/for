//
//  Cave.cpp
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

#include "Cave.h"

Cave::Cave(DungeonSpec spec) : Dungeon(spec)
{
    // Parent constructor has created tiles etc.
    // And called generation code for us

    name = "Cave";
    
    // Generate!
    Generate(spec);
    
    // Ready for path finding init
    InitPathfinding();
}

Cave::~Cave()
{
    // Let parent destroy alloc'ed structures
}

void Cave::Generate(DungeonSpec spec)
{
    // RANDOM SHIT
    RNG *rnd = RNG::getInstance();
    
    // Buffer to keep empty around accessible tiles
    int buffer = 10;
    
    // Make all areas
    int n=0;
    while( n < spec.numareas )
    {
        int ox = rnd->random_int(0,size.x-1);
        int oy = rnd->random_int(0,size.y-1);
        int sx = rnd->random_int(spec.area_minsize,spec.area_maxsize);
        int sy = rnd->random_int(spec.area_minsize,spec.area_maxsize);
        
        // Going outside map? Discard it
        if ( ox <= buffer || oy <= buffer || ox+sx >= size.x-buffer || oy+sy >= size.y-buffer )
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
    
    // Assign entry/exit special areas
    areas[0].type = AreaType::Entry;
    areas[1].type = AreaType::Exit;
    
    // Assign others randomly
    // Probabilites for die throw
    double probs[5];
    probs[0] = spec.defaultProb;
    probs[1] = spec.creaturesProb;
    probs[2] = spec.lootProb;
    probs[3] = spec.rareCreaturesProb;
    probs[4] = spec.rareLootProb;
    
    for (int i=2; i<areas.size(); i++)
    {
        // Throw die
        int d = rnd->throwDie(5, probs);
        
        switch ( d )
        {
            case 0: areas[i].type = AreaType::Default; break;
            case 1: areas[i].type = AreaType::Creatures; break;
            case 2: areas[i].type = AreaType::Loot; break;
            case 3: areas[i].type = AreaType::RareCreatures; break;
            case 4: areas[i].type = AreaType::RareLoot; break;
            default: throw "FUCKK";
        }
    }
    
    // Fill out tiles in areas so far
    // Just ground
    for( int i=0; i<areas.size(); i++ )
    {
        int ox = areas[i].pos.x;
        int oy = areas[i].pos.y;
        int sx = areas[i].size.x;
        int sy = areas[i].size.y;
        
        for ( int x=ox; x<ox+sx; x++)
            for ( int y=oy; y<oy+sy; y++ )
            {
                tiles[x][y].type = DungeonTileType::Floor;
                tiles[x][y].clipMask = true;
            }
    }
    
    // Connect every area to its nearest neighbor
    for ( int a=0; a<areas.size(); a++ )
    {
        // Find minimum dist
        double mindist = 10000000.0;
        DungeonArea *nearest;
        
        for (int b=0; b<areas.size(); b++)
        {
            // Same one?
            if ( a==b )
                continue;
            
            double d = (areas[a].center - areas[b].center).length();
            
            if ( d < mindist )
            {
                mindist = d;
                nearest = &areas[b];
            }
        }
        
        MakePassage(&areas[a], nearest);
    }
    
    // Keep connecting visgroups until only one remains
    int nsecs = 1000;
    while ( (nsecs = CreateVisGroups()) > 1 )
    {
        //cout << nsecs << "\n";
        
        // Find the two tiles from different groups with least distance between them
        // This is gay inefficient, should use bounding volumes or sometyhing
        double mindist = 1000000.0;
        veci aCoords;
        veci bCoords;
        
        DungeonTile *a;
        DungeonTile *b;
        
        // Random offsets to get random other starting tiles on other iterations
        int offsetx = rnd->random_int(0, size.x-1);
        int offsety = rnd->random_int(0, size.y-1);
        
        // Pick first (and not best but who cares)
        for ( int ax=0; ax<size.x; ax++ )
        {
            for ( int ay=0; ay<size.y; ay++ )
            {
                int indx = (ax+offsetx)%size.x;
                int indy = (ay+offsety)%size.y;
                
                if ( tiles[indx][indy].visgroup != -1 )
                {
                    a = &tiles[indx][indy];
                    aCoords = veci(indx,indy);
                }
            }
        }
        
        // Pick second of a different visgroup
        for ( int bx=0; bx<size.x; bx++ )
        {
            for ( int by=0; by<size.y; by++)
            {
                b = &tiles[bx][by];
                
                if ( a->visgroup != b->visgroup && b->visgroup != -1)
                {
                    vecd diff = vecd(aCoords.x-bx,aCoords.y-by);
                    double dist = diff.length();
                    
                    if ( dist < mindist )
                    {
                        mindist = dist;
                        bCoords = veci(bx,by);
                    }
                }
            }
        }
        
        // Create passage and rerun vis algorithm
        // SHITTY FUCK inefficient
        MakePassage(aCoords, bCoords);
        CreateVisGroups();
    }
    
    // Set edge tiles
    // Tiles are edge tiles if they are wall next to floor or vice versa
    SetEdgeFlags();
    
    // Roughen edges
    int steps = rnd->random_int(spec.roughenStepsMin, spec.roughenStepsMax);
    for ( int i=0; i<size.x; i++ )
    {
        for ( int j=0; j<size.y; j++ )
        {
            // Is this an edge? roughen it up
            if ( tiles[i][j].edgeMask )
            {
                int tempi = i;
                int tempj = j;
                
                // fuck first one up if wall
                tiles[tempi][tempj].clipMask = true;
                tiles[tempi][tempj].type = DungeonTileType::Floor;
                
                for ( int s=0; s<steps; s++ )
                {
                    // get random move dir
                    int movedir = rnd->random_int(0,3);
                    
                    int movex=0;
                    int movey=0;
                    switch( movedir )
                    {
                        case 0: movex=1; break;
                        case 1: movex=-1; break;
                        case 2: movey=1; break;
                        case 3: movey=-1; break;
                    }
                    
                    // set new coord
                    tempi += movex;
                    tempj += movey;
                    
                    // out of bounds?
                    if ( tempi <= 2 || tempi >= size.x-2 || tempj <= 2 || tempj >= size.y )
                        break;
                    
                    // Fuck it up
                    tiles[tempi][tempj].clipMask = true;
                    tiles[tempi][tempj].type = DungeonTileType::Floor;
                }
            }
        }
    }
    
    // Redo edge mask
    SetEdgeFlags();
    
    // Make nice edge tiles
    // If it has edgeMask true and is outside, make wall
    for ( int i=0; i<size.x; i++ )
        for ( int j=0; j<size.y; j++ )
        {
            DungeonTile *t = &tiles[i][j];
            
            if ( t->edgeMask == true && t->type == DungeonTileType::Outside )
                t->type = DungeonTileType::Wall;
        }
    
    // Fill out details
    
    // Populate with items
    
    // Populate with creatures
    
}

void Cave::MakePassage(vecd A, vecd B)
{
    veci mincoord = veci( min(A.x, B.x), min(A.y,B.y) );
    veci maxcoord = veci( max(A.x, B.x), max(A.y,B.y) );
    
    // Extra space to make sure we don't cut it off
    mincoord = mincoord - veci(1,1);
    maxcoord = maxcoord + veci(1,1);
    
    // Line dist vetors parameterization
    vecd av = A;
    vecd nv = A-B;
    nv = (1/nv.length())*nv;
    
    // Default width of passages
    double pwidth = 1.0;
    
    // Loop over eligible tiles
    for ( int ti=mincoord.x; ti<=maxcoord.x; ti++ )
        for ( int tj=mincoord.y; tj<maxcoord.y; tj++ )
        {
            // Out of bounds?
            if ( ti<0 || ti>=size.x || tj<0 || tj>=size.y )
                continue;
            
            vecd p = vecd((double)ti,(double)tj);
            
            double dist = (av - p - dot(av-p,nv)*nv).length();
            
            if ( dist <= pwidth )
            {
                // Add as accessible
                tiles[ti][tj].clipMask = true;
                tiles[ti][tj].type = DungeonTileType::Floor;
            }
        }
}

void Cave::MakePassage(DungeonArea *A, DungeonArea *B)
{
    // CONNECT
    MakePassage(A->center, B->center);
}

veci Cave::GetPlayerSpawnCoords()
{
    // Get entry area
    DungeonArea entry = areas[0];
    
    // Somewhere near the entry tile
    // TODO: Better method (entrance tile, like stairs)
    return (veci)entry.center + veci(1,1);
}