//
//  World.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "World.h"

#include "noise.h"
#include "noiseutils.h"
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
    // Random numbers
    RNG *rnd = RNG::getInstance();
    
    module::Perlin myModule;
    myModule.SetSeed((int)time(0));
    
    // Good parameters:
    // Octave 4
    // Freq 2
    
    // TMP DBG testing of different Perlin parameters
    /*
     int octaves[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
     
     for (int o=0; o<10; o++ )
     {
     for ( double f=1.0; f<16.0; f++ )
     {
     
     myModule.SetOctaveCount(octaves[o]);
     myModule.SetFrequency(f);
     myModule.SetPersistence(0.4);
     
     utils::NoiseMap heightMap;
     utils::NoiseMapBuilderPlane heightMapBuilder;
     heightMapBuilder.SetSourceModule (myModule);
     heightMapBuilder.SetDestNoiseMap (heightMap);
     heightMapBuilder.SetDestSize (512, 512);
     heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
     heightMapBuilder.Build ();
     
     utils::RendererImage renderer;
     utils::Image image;
     renderer.SetSourceNoiseMap (heightMap);
     renderer.SetDestImage (image);
     renderer.ClearGradient ();
     renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
     renderer.AddGradientPoint (-0.900, utils::Color (  0,   0, 255, 255)); // shallow
     renderer.AddGradientPoint ( -0.600, utils::Color (  0, 128, 255, 255)); // shore
     renderer.AddGradientPoint ( -0.45, utils::Color (240, 240,  64, 255)); // sand
     renderer.AddGradientPoint ( 0.000, utils::Color ( 32, 160,   0, 255)); // grass
     renderer.AddGradientPoint ( 0.2750, utils::Color (224, 224,   0, 255)); // dirt
     renderer.AddGradientPoint ( 0.8500, utils::Color (128, 128, 128, 255)); // rock
     renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
     renderer.EnableLight ();
     renderer.SetLightContrast (2.0); // Triple the contrast
     renderer.SetLightBrightness (2.0); // Double the brightness
     renderer.Render ();
     
     utils::WriterBMP writer;
     writer.SetSourceImage (image);
     writer.SetDestFilename ("out/" + numberToString(octaves[o]) + "_" + numberToString(f) + ".bmp");
     writer.WriteDestFile ();
     
     cout << octaves[o] << " " << f << "\n";
     }
     }
     */
    
    int octave = 4;
    double freq = 2;
    
    myModule.SetOctaveCount(octave);
    myModule.SetFrequency(freq);
    myModule.SetPersistence(0.4);
    
    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule (myModule);
    heightMapBuilder.SetDestNoiseMap (heightMap);
    heightMapBuilder.SetDestSize (size.x, size.y);
    heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
    heightMapBuilder.Build ();
    
    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap (heightMap);
    renderer.SetDestImage (image);
    renderer.ClearGradient ();
    renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
    renderer.AddGradientPoint (spec.lakeCut, utils::Color (  0,   0, 255, 255)); // shallow
    renderer.AddGradientPoint ( spec.flatCut, utils::Color ( 32, 160,   0, 255)); // grass
    renderer.AddGradientPoint ( spec.hillyCut, utils::Color (224, 224,   0, 255)); // dirt, hills
    renderer.AddGradientPoint ( spec.mountainCut, utils::Color (128, 128, 128, 255)); // rock
    renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
    renderer.EnableLight ();
    renderer.SetLightContrast (2.0); // Triple the contrast
    renderer.SetLightBrightness (2.0); // Double the brightness
    renderer.Render ();
    
    // TMP DBG: write heightmap to image
    utils::WriterBMP writer;
    writer.SetSourceImage (image);
    writer.SetDestFilename ("heighmap.bmp");
    writer.WriteDestFile ();
    
    // Save heightmap info and assign tile type from height
    for ( int x=0; x<size.x; x++ )
        for ( int y=0; y<size.y; y++ )
        {
            WorldTile *currTile = &tiles[x][y];
            double h = heightMap.GetValue(x, y);
            
            currTile->height = h;
            
            if ( h < spec.lakeCut )
                currTile->type = WorldTileType::Lake;
            else if ( h < spec.flatCut )
                currTile->type = WorldTileType::Dirt;
            else if ( h < spec.hillyCut )
                currTile->type = WorldTileType::Hilly;
            else
                currTile->type = WorldTileType::Mountains;
        }
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