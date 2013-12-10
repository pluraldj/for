//
//  Creature.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Creature__
#define __forogue__Creature__

#include <iostream>
#include <string>

#include "Entity.h"
#include "Armor.h"

class Creature : public Entity
{
public:
    Creature();
    ~Creature();
    
    void TakeDamage(int dmg);
    void Die();
    
    int xpOnKill;
    int HP;
    int HPmax;
    int healingRate;
    int AC;
    int sequence;
    int AP;
    int APmax;
    
    int meleeDmg;
    double critChance;
    
    Armor baseArmor;        // Natural baseline armor without other armor worn
    
    string symbol;
};


#endif /* defined(__forogue__Creature__) */
