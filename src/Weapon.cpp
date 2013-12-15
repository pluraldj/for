//
//  Weapon.cpp
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


#include "Weapon.h"

Weapon::Weapon()
{
    // Default values that should all be overwritten when the item is constructed
    name = "Weapon";
    weaponType = WeaponType::None;
    
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