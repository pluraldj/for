//
//  Entity.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Entity__
#define __forogue__Entity__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <string>

#include "Utils.h"

using namespace std;

enum class EntityType {
    None,            // Should never be used
    
    Rock,
    
    Critter,         // Should not be used, use subtype
    Player,          // ONLY one allowed
    Human,
    Ghoul,
    Mutant,
    
    Animal,
    MutatedAnimal,
    
    Container,       // Chests etc.
    Corpse,
    
    StairsDown,
    StairsUp,
    Trap,            // AFTER it is discovered, invisible until
    OpenDoor,
    ClosedDoor,
    Misc,            // Consoles, stations etc.
    
    Caps,
    Melee,
    Gun,
    Tool,
    Armor,           // Wearable
    Ammo,
    Edible,          // Stimpaks, HP stuff, food
    Readable         // Notes, skill books
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
