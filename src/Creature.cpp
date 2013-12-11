//
//  Creature.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Creature.h"

Creature::Creature()
{
    xpOnKill = 1;
    
    HPmax = 1;
    healingRate = 1;
    
    AC = 1;
    sequence = 1;
    APmax = 1;
    
    meleeDmg = 1;
    critChance = 0.1;
}

Creature::~Creature()
{
}

// Lose some HP from an attack and maybe die as a result
void Creature::TakeDamage(int dmg)
{
    HP -= dmg;
    
    if ( HP < 1 )
        Die();
}

// He's dead, Jim
void Creature::Die()
{
    // Leave a corpse and items
    // TODO
}