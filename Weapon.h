//
//  Weapon.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Weapon__
#define __forogue__Weapon__

#include <iostream>

#include "Item.h"
#include "Ammo.h"

enum WeaponType { WeaponNone, Melee, SmallGun, BigGun, Explosive, Energy, Thrown, Unarmed };
enum AttackType { AttackNone, Single, Aimed, Burst, Punch, Swing, Thrust, Throw };
enum DamageType { Normal, Laser, Fire, Plasma, Electrical, Explosion, EMP };

struct AttackMode
{
public:
    AttackMode()
    {
        name = "Single";
        attackType = AttackType::AttackNone;
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
