//
//  DungeonSpec.cpp
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


#include "DungeonSpec.h"

DungeonSpec::DungeonSpec()
{
    type = DungeonType::Cave;
    
    numareas = 2;
    
    minsize = 50;
    maxsize = 50;
    
    area_minsize = 10;
    area_maxsize = 15;
    
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