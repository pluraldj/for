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
    name = "Unknown Dungeon";
    
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





