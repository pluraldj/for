//
//  WorldSpec.h
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
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


#ifndef __forogue__WorldSpec__
#define __forogue__WorldSpec__

#define _XOPEN_SOURCE_EXTENDED

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
    // first segment is -1  to lakeCut, others are preceding to their value.
    // mountainCut must be 1.0, should do this explicitly
    
    double lakeCut, flatCut, hillyCut, mountainCut;
};

#endif /* defined(__forogue__WorldSpec__) */
