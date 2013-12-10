//
//  DungeonSpec.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "DungeonSpec.h"

DungeonSpec::DungeonSpec()
{
    type = DungeonType::Cave;
    
    numareas = 120;
    
    minsize = 200;
    maxsize = 400;
    
    area_minsize = 2;
    area_maxsize = 7;
    
    // Probabilities of assigning area type
    // THESE MUST ADD TO ONE YOU NUB
    defaultProb = 0.2;
    creaturesProb = 0.5;
    lootProb = 0.2;
    rareCreaturesProb = 0.05;
    rareLootProb = 0.05;
    
    // Number of roughen-up steps
    roughenStepsMin = 2;
    roughenStepsMax = 5;
}