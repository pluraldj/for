//
//  DungeonSpec.h
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
