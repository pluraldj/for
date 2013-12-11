//
//  WorldSpec.h
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__WorldSpec__
#define __forogue__WorldSpec__

#include <iostream>
#include <string>

using namespace std;

// Specification of parameters for wasteland generation
// Like percentage of area types, towns etc.
struct WorldSpec
{
public:
    WorldSpec();
    
    // Size in number of tiles
    int minsize,maxsize;
    
    // Density of sites - x per unit area ≈ prob. of it being an interesting tile
    double siteDensity;
    
    // Cutoffs for segmenting areas according to heightmap value
    // Values are in the range [-1;1]
    // first segment is -1  to seaCut, others are preceding to their value.
    // snowCut must be 1.0, should do this explicitly
    double seaCut, shoreCut, grassCut, dirtCut, mountainCut, snowCut;
};

#endif /* defined(__forogue__WorldSpec__) */
