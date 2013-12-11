//
//  Weapon.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Weapon.h"

Weapon::Weapon()
{
    // Default values that should all be overwritten when the item is constructed
    name = "Weapon";
    weaponType = WeaponType::WeaponNone;
    
    weight = 0;
    baseValue = 0;
    
    minDmg = 0;
    maxDmg = 0;
    
    ammoType = AmmoType::AmmoNone;
    ammoCapacity = 0;
    currAmmo = 0;
    
    strengthReq = 0;
    condition = 0.5;
}

Weapon::~Weapon()
{
}