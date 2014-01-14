//
//  Dungeon.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
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


#include "Dungeon.h"
#include "Utils.h"

Dungeon::Dungeon(DungeonSpec spec) : Location()
{
    name = "Unknown Cave";
    
    // Random size
    RNG *rnd = RNG::getInstance();
    
    size.x = rnd->random_int(spec.minsize,spec.maxsize);
    size.y = rnd->random_int(spec.minsize,spec.maxsize);
    
    // Allocate space for tiles
    tiles = new DungeonTile*[size.x];
    for(int i=0; i<size.x; i++)
        tiles[i] = new DungeonTile[size.y];
    
    // init tiles
    for(int i=0; i<size.x; i++)
        for(int j=0; j<size.y; j++)
        {
            // empty tiles
            tiles[i][j].type = DungeonTileType::Outside;
            
            // Not accessible
            tiles[i][j].clipMask = false;
            
            // Not edges
            tiles[i][j].edgeMask = false;
        }
    
    activeEnts = new vector<Entity*>;
    
    aStarSearcher = NULL;
    
    // Generate!
    Generate(spec);
}

Dungeon::~Dungeon()
{
    if ( tiles != NULL )
    {
        for (int i=0; i<size.x; i++)
            delete[] tiles[i];
        
        delete[] tiles;
    }
    
    if ( aStarSearcher )
        delete aStarSearcher;
}

// Draw tiles as list of strings (horizontal lines of symbols)
// Remember to dealloc returned array after use!
// fow = obscure with fog of war (yes/no)
wstring* Dungeon::drawRect(veci upperleft, veci window, bool fow, Visibility *vis)
{
    int posx = upperleft.x;
    int posy = upperleft.y;
    int width = window.x;
    int height = window.y;
    
    // Allocate new string array
    wstring *result = new wstring[height];
    
    // Loop over region
    for(int j=0; j<height; j++)
    {
        // This line
        wstring line = L"";
        
        // Offset to find position in logical coords
        int y = posy+j;
        
        for(int i=0; i<width; i++)
        {
            // Offset to find position in logical coords
            int x = posx+i;
            
            // Outside stored map? Then draw as dark
            if ( x < 0 || x >= size.x || y < 0 || y >= size.y )
            {
                line.append( L" " );
                continue;
            }
            
            // Completely unexplored?
            if ( fow && vis->tiles[x][y] == VisibilityType::Dark )
            {
                line.append( L" " );
            }
            // Obscured by fog of war?
            else if ( fow && vis->tiles[x][y] == VisibilityType::Fow )
            {
                DungeonTile *currTile = &tiles[x][y];
                
                // Only keep persistent structures
                // Keep walls, don't keep ground/other stuff
                if ( currTile->type == DungeonTileType::Wall )
                {
                    line.append( currTile->DrawSymbol() );
                }
                // Obscure it
                else
                {
                    line.append( L"\"" );
                }
            }
            // Completely visible
            else
            {
                // Just draw it
                line.append( tiles[x][y].DrawSymbol() );
            }
        }
        
        // Append last X sice
        result[j] = line;
    }
    
    return result;
}

void Dungeon::Generate(DungeonSpec spec)
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
        
        // Going outside map? Fuck it then
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
    
    // Ready for path finding init
    InitPathfinding();
}

void Dungeon::MakePassage(vecd A, vecd B)
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

void Dungeon::MakePassage(DungeonArea *A, DungeonArea *B)
{
    // CONNECT
    MakePassage(A->center, B->center);
}

// Set edge flag on tiles
// Tiles are edge tiles if they are passable next to impassable or vice versa
void Dungeon::SetEdgeFlags()
{
    for ( int i=2; i<size.x-2; i++ )
        for ( int j=2; j<size.y-2; j++ )
        {
            DungeonTile *center = &tiles[i][j];
            
            // Other tiles to test
            DungeonTile* surrounding[8];
            surrounding[0] = &tiles[i+1][j];
            surrounding[1] = &tiles[i+1][j+1];
            surrounding[2] = &tiles[i+1][j-1];
            surrounding[3] = &tiles[i][j+1];
            surrounding[4] = &tiles[i][j-1];
            surrounding[5] = &tiles[i-1][j];
            surrounding[6] = &tiles[i-1][j+1];
            surrounding[7] = &tiles[i-1][j-1];
            
            // This mask
            bool mask = center->clipMask;
            
            // Test surrounding
            bool foundEdge = false;
            for ( int s=0; s<8; s++ )
            {
                if ( surrounding[s]->clipMask != mask )
                {
                    center->edgeMask = true;
                    foundEdge = true;
                    continue;
                }
            }
            
            center->edgeMask = foundEdge;
        }
}

int Dungeon::CreateVisGroups()
{
    // Cluster connected tiles into groups to determine how many isolated sections of the dungeon there are
    int nsec = 0;
    
    // Reset visgroups
    for ( int i=0; i<size.x; i++)
        for ( int j=0; j<size.y; j++ )
        {
            tiles[i][j].visgroup = -1;
        }
    
    // Iterate and fill recursively
    for (int a=0; a<areas.size(); a++)
    {
        DungeonArea *currArea = &areas[a];
        
        // Start in center of area
        veci initTile = veci((int)currArea->center.x, (int)currArea->center.y);
        
        // Recursively fill with this visgroup
        bool filledNew = recursiveVisFill(initTile.x, initTile.y, nsec);
        if ( filledNew )
        {
            nsec++;
        }
    }
    
    return nsec;
}

bool Dungeon::recursiveVisFill(int x, int y, int group)
{
    // Outside world?
    if ( x<0 || x>=size.x || y<0 || y>=size.y )
        return false;
    
    // Is this one already filled?
    if ( tiles[x][y].visgroup != -1 )
        return false;
    
    // Color this one and return true (we painted at least one)
    // First we need to color all connected though
    stack<pair<int,int>> toCheck;
    toCheck.push(pair<int,int>(x,y));
    
    pair<int,int> next;
    while ( !toCheck.empty() )
    {
        next = toCheck.top();
        toCheck.pop();
        
        x = next.first;
        y = next.second;
        
        // Neighbors to check
        pair<int,int> neighbors[8];
        
        neighbors[0] = pair<int,int>(x+1,y);
        neighbors[1] = pair<int,int>(x+1,y+1);
        neighbors[2] = pair<int,int>(x+1,y-1);
        neighbors[3] = pair<int,int>(x,y+1);
        neighbors[4] = pair<int,int>(x,y-1);
        neighbors[5] = pair<int,int>(x-1,y);
        neighbors[6] = pair<int,int>(x-1,y+1);
        neighbors[7] = pair<int,int>(x-1,y-1);
        
        for(int i=0; i<7; i++)
        {
            int newx = neighbors[i].first;
            int newy = neighbors[i].second;
            
            // Outside world?
            if ( x<0 || x>=size.x || y<0 || y>=size.y )
                continue;
            
            DungeonTile *curr = &tiles[newx][newy];
            
            if ( curr->clipMask == true && curr->visgroup == -1 )
            {
                curr->visgroup = group;
                toCheck.push( neighbors[i] );
            }
        }
    }
    
    return true;
}

veci Dungeon::GetPlayerSpawnCoords()
{
    // Get entry area
    DungeonArea entry = areas[0];
    
    // Somewhere near the entry tile
    return (veci)entry.center + veci(1,1);
}

void Dungeon::InitPathfinding()
{
    if ( aStarSearcher )
        delete aStarSearcher;
        
    aStarSearcher = new AStarSearcher(this);
}

void Dungeon::Dump(string path)
{
    wstring *wholeMap = drawRect(veci(0,0), size, false, NULL);
    
    wofstream outfile;
    outfile.open(path.c_str());
    
    for ( int i=0; i<size.y; i++ )
    {
        outfile << wholeMap[i] << "\n";
    }
    
    outfile.close();
}

void Dungeon::DumpVisGroups(string path)
{
    ofstream outfile;
    outfile.open(path.c_str());
    
    for( int y=0; y<size.y; y++)
    {
        for ( int x=0; x<size.x; x++)
        {
            int vis = tiles[x][y].visgroup;
            
            if ( vis == -1 )
                outfile << " ";
            else
                outfile << numberToString(vis);
        }
        outfile << "\n";
    }
    
    outfile.close();
}

void Dungeon::DumpEdgeMask(string path)
{
    ofstream outfile;
    outfile.open(path.c_str());
    
    for( int y=0; y<size.y; y++)
    {
        for ( int x=0; x<size.x; x++)
        {
            bool mask = tiles[x][y].edgeMask;
            
            if ( mask )
                outfile << "1";
            else
                outfile << " ";
        }
        outfile << "\n";
    }
    
    outfile.close();
}

Tile *Dungeon::GetTile(int x, int y)
{
    if ( x<0 || y<0 || x>=size.x || y>=size.y )
        return NULL;
    else
        return &tiles[x][y];
}





