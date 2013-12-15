//
//  Weapon.h
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


#ifndef __forogue__Weapon__
#define __forogue__Weapon__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

#include "Item.h"
#include "Ammo.h"

enum class WeaponType { None, Melee, SmallGun, BigGun, Explosive, Energy, Thrown, Unarmed };
enum class AttackType { None, Single, Aimed, Burst, Punch, Swing, Thrust, Throw };
enum class DamageType { Normal, Laser, Fire, Plasma, Electrical, Explosion, EMP };

struct AttackMode
{
public:
    AttackMode()
    {
        name = "Single";
        attackType = AttackType::None;
        range = 0.0;
        rounds = 1;
        apCost = 1;
    }
    
    string name;
    AttackType attackType;
    double range;
    int rounds;
    int apCost;
};

class Weapon : public Item
{
public:
    Weapon();
    ~Weapon();
    
    WeaponType weaponType;
    
    DamageType damageType;
    
    vector<AttackMode> attacks;
    
    int minDmg,maxDmg;
    
    AmmoType ammoType;
    int ammoCapacity;
    int currAmmo;
    
    int strengthReq;
    
    double condition;   // 0.0 - 1.0 percentage
};

#endif /* defined(__forogue__Weapon__) */
