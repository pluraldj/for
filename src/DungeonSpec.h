//
//  DungeonSpec.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__DungeonSpec__
#define __forogue__DungeonSpec__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <random>
#include <math.h>

using namespace std;

enum class DungeonType { Cave, Random };

// Specification of parameters for dungeon creation
struct DungeonSpec
{
    DungeonSpec();
    
    DungeonType type;
    
    int numareas;
    
    int minsize,maxsize;
    
    int area_minsize, area_maxsize;
    
    double defaultProb, creaturesProb, lootProb, rareCreaturesProb, rareLootProb;
  
    int roughenStepsMin, roughenStepsMax;
};

#endif /* defined(__forogue__DungeonSpec__) */
