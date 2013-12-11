//
//  Armor.h
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Armor__
#define __forogue__Armor__

#include <iostream>

#include "Item.h"

struct DmgMods
{
public:
    DmgMods(){ DT=0; DR=0.0; }
    
    int DT;
    double DR;
};

class Armor : public Item
{
public:
    Armor();
    
    DmgMods normal;
    DmgMods laser;
    DmgMods fire;
    DmgMods plasma;
    DmgMods electrical;
    DmgMods explosive;
    DmgMods emp;
};

#endif /* defined(__forogue__Armor__) */
