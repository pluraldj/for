//
//  Entity.h
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


#ifndef __forogue__Entity__
#define __forogue__Entity__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>
#include <string>

#include "Utils.h"

using namespace std;

enum class EntityType {
    None,            // Should never be used, overwrite after instantiation
    
    Critter,         // Should not be used, use subtype
    
    Player,          // ONLY one allowed
    
    // Use subtypes generally
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
    
    wstring DrawSymbol();    // Draw generic symbol for type
    
    // Overriding specific symbol, for example rats use "r" instead of generic animal "a"
    wstring specificSymbol;
    
    string name;
    EntityType type;
    
    veci location;  // Tile location
    
private:
};

#endif /* defined(__forogue__Entity__) */
