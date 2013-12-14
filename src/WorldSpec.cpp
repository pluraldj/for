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
    minsize = 100;
    maxsize = 100;
    
    siteDensity = 0.1;
    
    lakeCut = -0.3;
    flatCut = 0.3;
    hillyCut = 0.6;
    mountainCut = 0.9;
}