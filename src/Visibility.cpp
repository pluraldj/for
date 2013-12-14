//
//  Visibility.cpp
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Visibility.h"
#include "Dungeon.h"
#include "World.h"
#include "Character.h"

// Construct Visibility object for vis in dungeons
Visibility::Visibility(Dungeon *_dungeon, Character *_owner)
{
    if ( !_dungeon )
        throw "Dungeon not init'd before creating vis!";
    
    if ( !_owner )
        throw "Character not init'd before creating vis!";
    
    dungeon = _dungeon;
    world = NULL;
    
    owner = _owner;
    size = dungeon->size;

    // Allocate space for tiles
    tiles = new VisibilityType*[size.x];
    for(int i=0; i<size.x; i++)
        tiles[i] = new VisibilityType[size.y];
    
    lightMap = new double*[size.x];
    for(int i=0; i<size.x; i++)
        lightMap[i] = new double[size.y];
    
    ClearVis();
}

// Construct Visibility object for vis in overworld
Visibility::Visibility(World *_world, Character *_owner)
{
    if ( !_world )
        throw "World not init'd before creating vis!";
    
    if ( !_owner )
        throw "Character not init'd before creating vis!";
    
    dungeon = NULL;
    world = _world;
    
    owner = _owner;
    size = world->size;
    
    // Allocate space for tiles
    tiles = new VisibilityType*[size.x];
    for(int i=0; i<size.x; i++)
        tiles[i] = new VisibilityType[size.y];
    
    lightMap = new double*[size.x];
    for(int i=0; i<size.x; i++)
        lightMap[i] = new double[size.y];
    
    ClearVis();
}

Visibility::~Visibility()
{
    
}

void Visibility::ClearVis()
{
    for ( int i=0; i<size.x; i++)
        for ( int j=0; j<size.y; j++ )
            tiles[i][j] = VisibilityType::Dark;
}

// Vis calculation depends on where we are (world or in specific location)
void Visibility::UpdateVis()
{
    if ( world == NULL && dungeon != NULL )
        UpdateVisInDungeon();
    else if ( world != NULL & dungeon == NULL )
        UpdateVisInWorld();
    else
        return;
}

// Stolen from
// http://roguebasin.roguelikedevelopment.org/index.php?title=FOV_using_recursive_shadowcasting_-_improved
void Visibility::UpdateVisInDungeon()
{
    // Start from character position
    veci origin = owner->location;
    int startx = origin.x;
    int starty = origin.y;
    
    int width = size.x;
    int height = size.y;
    
    // Reset Light map
    // Values <= 0 mean not in FOV, values > 0 mean they are in FOV
    for ( int i=0; i<width; i++ )
        for ( int j=0; j<height; j++ )
            lightMap[i][j] = 0.0;
    
    // Light initial cell
    lightMap[startx][starty] = 1.0;
    
    // Diagonal directions
    veci diagonals[4];
    diagonals[0] = veci(1,1);
    diagonals[1] = veci(1,-1);
    diagonals[2] = veci(-1,1);
    diagonals[3] = veci(-1,-1);
    
    for ( int d=0; d<4; d++ )
    {
        veci diag = diagonals[d];
        
        CastLight(1, 1.0, 0.0, 0, diag.x, diag.y, 0);
        CastLight(1, 1.0, 0.0, diag.x, 0, 0, diag.y);
    }
    
    // Interpret light map as Vis info
    for (int i=0; i<width; i++)
        for ( int j=0; j<height; j++ )
        {
            double l = lightMap[i][j];
            
            // Fallen out of sight?
            if ( l <= 0.0 )
            {
                if ( tiles[i][j] == VisibilityType::Light )
                    tiles[i][j] = VisibilityType::Fow;
            }
            else
            {
                // Lit up
                tiles[i][j] = VisibilityType::Light;
            }
        }
}

void Visibility::UpdateVisInWorld()
{
    
}

void Visibility::CastLight(int row, double start, double end, int xx, int xy, int yx, int yy)
{
    // Maximum radius of FOV
    const double radius = 100.0;
    
    // Start from character position
    veci origin = owner->location;
    int startx = origin.x;
    int starty = origin.y;
    
    int width = size.x;
    int height = size.y;
    
    double newStart = 0.0;
    
    if ( start < end )
        return;
    
    bool blocked = false;
    
    for (int distance = row; distance <= radius && !blocked; distance++ )
    {
        int deltaY = -distance;
        for (int deltaX = -distance; deltaX <= 0; deltaX++)
        {
            int currentX = startx + deltaX * xx + deltaY * xy;
            int currentY = starty + deltaX * yx + deltaY * yy;
            
            double leftSlope = (deltaX - 0.5f) / (deltaY + 0.5f);
            double rightSlope = (deltaX + 0.5f) / (deltaY - 0.5f);
        
            if (!(currentX >= 0 && currentY >= 0 && currentX < width && currentY < height) || start < rightSlope)
            {
                continue;
            }
            else if (end > leftSlope)
            {
                break;
            }
            
            //check if it's within the lightable area and light if needed
            if (vecd(deltaX,deltaY).length() <= radius)
            {
                double bright = (1.0 - (vecd(deltaX,deltaY).length() / radius));
                lightMap[currentX][currentY] = bright;
            }
            
            if (blocked)
            {
                //previous cell was a blocking one
                if (dungeon->tiles[currentX][currentY].clipMask == false )
                {
                    //hit a wall
                    newStart = rightSlope;
                    continue;
                }
                else
                {
                    blocked = false;
                    start = newStart;
                }
            }
            else
            {
                if (dungeon->tiles[currentX][currentY].clipMask == false && distance < radius)
                {
                    //hit a wall within sight line
                    blocked = true;
                    CastLight(distance + 1, start, leftSlope, xx, xy, yx, yy);
                    newStart = rightSlope;
                }
            }
        }
    }
}















