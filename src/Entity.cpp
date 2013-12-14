//
//  Entity.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Entity.h"

#include "TileSet.h"

Entity::Entity()
{
    name = "Entity";
    location = veci(0,0);
    type = EntityType::None;
}

Entity::~Entity()
{
}

wstring Entity::DrawSymbol()
{
    if ( specificSymbol != L"" )
        return specificSymbol;
    
    return TileSet::getInstance()->EntitySymbol(type);
    
    // OLD
    /*
    switch ( type )
    {
        case EntityType::None: return "e";
        
        // Useless background stuff
        case EntityType::Rock: return "*";
            
        // Creature supertypes
        case EntityType::Critter: return "C";
        case EntityType::Player: return "@";
            
        // Intelligent beings
        case EntityType::Human: return "@";
        case EntityType::Ghoul: return "g";
        case EntityType::Mutant: return "M";
            
        // Animals
        case EntityType::Animal: return "a";
        case EntityType::MutatedAnimal: return "A";
            
        // Stuff with stuff in it
        case EntityType::Container: return "§";
        case EntityType::Corpse: return "§";
            
        // Miscellaneous objects
        case EntityType::StairsDown: return ">";
        case EntityType::StairsUp: return "<";
        case EntityType::Trap: return "^";
        case EntityType::OpenDoor: return "/";
        case EntityType::ClosedDoor: return "+";
        case EntityType::Misc: return "&";
            
        // Items, can be picked up
        case EntityType::Caps: return "$";
        case EntityType::Melee: return "(";
        case EntityType::Gun: return "}";
        case EntityType::Tool: return "]";
        case EntityType::Armor: return "[";
        case EntityType::Ammo: return ";";
        case EntityType::Edible: return "%";
        case EntityType::Readable: return "?";
    }
    
    return "e";
    */
}