//
//  World.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "World.h"

#include "noise.h"
using namespace noise;

World::World(WorldSpec spec)
{
    name = "Wasteland";
 
    // Random size
    RNG *rnd = RNG::getInstance();
    
    size.x = rnd->random_int(spec.minsize,spec.maxsize);
    size.y = rnd->random_int(spec.minsize,spec.maxsize);
    
    // Allocate space for tiles
    tiles = new WorldTile*[size.x];
    for(int i=0; i<size.x; i++)
        tiles[i] = new WorldTile[size.y];
    
    // init tiles
    // NOPE, just use standard initialization when alloc'ed
    
    // Generate!
    Generate(spec);
}

string* World::drawRect(veci upperleft, veci window, bool fow)
{
    int posx = upperleft.x;
    int posy = upperleft.y;
    int width = window.x;
    int height = window.y;
    
    // Allocate new string array
    string *result = new string[height];
    
    // Loop over region
    for(int j=0; j<height; j++)
    {
        // This line
        string line = "";
        
        // Offset to find position in logical coords
        int y = posy+j;
        
        for(int i=0; i<width; i++)
        {
            // Offset to find position in logical coords
            int x = posx+i;
            
            // Outside stored map? Then draw as dark
            if ( x < 0 || x >= size.x || y < 0 || y >= size.y )
            {
                line.append( " " );
                continue;
            }
            
            // Completely unexplored?
            if ( fow && tiles[x][y].visible == false )
            {
                line.append( " " );
            }
            // Visible
            else
            {
                WorldTile *currTile = &tiles[x][y];
                
                // Just draw
                line.append( currTile->DrawSymbol() );
                
            }
        }
        
        // Append last X sice
        result[j] = line;
    }
    
    return result;
}

void World::Generate(WorldSpec spec)
{
    // Perlin noise module
    module::Perlin perlinModule;
}

void World::Dump(string path)
{
    string *wholeMap = drawRect(veci(0,0), size, false);
    
    ofstream outfile;
    outfile.open(path);
    
    for ( int i=0; i<size.y; i++ )
    {
        outfile << wholeMap[i] << "\n";
    }
    
    outfile.close();
}