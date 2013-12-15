//
//  Creature.cpp
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