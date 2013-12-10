//
//  Entity.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Entity.h"

Entity::Entity()
{
    name = "Entity";
    location = veci(0,0);
    type = EntityType::EntNone;
}

Entity::~Entity()
{
}

string Entity::DrawSymbol()
{
    if ( specificSymbol != "" )
        return specificSymbol;
    
    switch ( type )
    {
        case EntNone: return "e";
        
        // Useless background stuff
        case EntRock: return "*";
            
        // Creature supertypes
        case EntCritter: return "C";
        case EntPlayer: return "@";
            
        // Intelligent beings
        case EntHuman: return "@";
        case EntGhoul: return "g";
        case EntMutant: return "M";
            
        // Animals
        case EntAnimal: return "a";
        case EntMutatedAnimal: return "A";
            
        // Stuff with stuff in it
        case EntContainer: return "§";
        case EntCorpse: return "§";
            
        // Miscellaneous objects
        case EntStairsDown: return ">";
        case EntStairsUp: return "<";
        case EntTrap: return "^";
        case EntOpenDoor: return "/";
        case EntClosedDoor: return "+";
        case EntMisc: return "&";
            
        // Items, can be picked up
        case EntCaps: return "$";
        case EntMelee: return "(";
        case EntGun: return "}";
        case EntTool: return "]";
        case EntArmor: return "[";
        case EntAmmo: return ";";
        case EntEdible: return "%";
        case EntReadable: return "?";
            
    }
    
    return "e";
}