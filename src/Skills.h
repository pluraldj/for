//
//  Skills.h
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


#ifndef __forogue__Skills__
#define __forogue__Skills__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

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
