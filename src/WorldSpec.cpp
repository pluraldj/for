//
//  WorldSpec.cpp
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "WorldSpec.h"

WorldSpec::WorldSpec()
{
    // Default values
    minsize = 200;
    maxsize = 500;
    
    siteDensity = 0.1;
    
    seaCut = -0.8;
    shoreCut = -0.6;
    grassCut = -0.1;
    dirtCut = 0.4;
    mountainCut = 0.8;
    snowCut = 1.0;
}