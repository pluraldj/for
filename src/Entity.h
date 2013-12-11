//
//  Entity.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Entity__
#define __forogue__Entity__

#include <iostream>
#include <string>

#include "Utils.h"

using namespace std;

enum EntityType {
    EntNone,            // Should never be used
    
    EntRock,
    
    EntCritter,         // Should not be used, use subtype
    EntPlayer,          // ONLY one allowed
    EntHuman,
    EntGhoul,
    EntMutant,
    
    EntAnimal,
    EntMutatedAnimal,
    
    EntContainer,       // Chests etc.
    EntCorpse,
    
    EntStairsDown,
    EntStairsUp,
    EntTrap,            // AFTER it is discovered, invisible until
    EntOpenDoor,
    EntClosedDoor,
    EntMisc,            // Consoles, stations etc.
    
    EntCaps,
    EntMelee,
    EntGun,
    EntTool,
    EntArmor,           // Wearable
    EntAmmo,
    EntEdible,          // Stimpaks, HP stuff, food
    EntReadable         // Notes, skill books
};

class Entity
{
public:
    Entity();
    virtual ~Entity();
    
    string DrawSymbol();    // Draw generic symbol for type
    
    // Overriding specific symbol, for example rats use "r" instead of generic animal "a"
    string specificSymbol;
    
    string name;
    EntityType type;
    
    veci location;  // Tile location
    
private:
};

#endif /* defined(__forogue__Entity__) */
