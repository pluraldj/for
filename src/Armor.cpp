//
//  Armor.cpp
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Armor.h"

Armor::Armor()
{
    name = "Armor";
    weight = 1;
    baseValue = 1;
    
    // Don't do anything to DT/DR, they all init to 0.
    // Exception: EMP, since pretty much everything is immune
    emp.DT = 0;
    emp.DR = 5.0;
}