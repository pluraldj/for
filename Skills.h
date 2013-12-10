//
//  Skills.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Skills__
#define __forogue__Skills__

#include <iostream>

struct Skills
{
public:
    Skills();
    
    // combat
    int bigGuns;
    int smallGuns;
    int energyWeapons;
    int meleeWeapons;
    int throwing;
    int unarmed;
    
    // active
    int doctor;
    int firstAid;
    int lockpick;
    int repair;
    int science;
    int sneak;
    int steal;
    int traps;
    
    // passive
    int barter;
    int gambling;
    int outdoorsman;
    int speech;
};

#endif /* defined(__forogue__Skills__) */
