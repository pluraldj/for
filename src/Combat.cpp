//
//  Combat.cpp
//  forogue
//
//  Created by Lasse Carstensen on 27/12/13.
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

#include "Combat.h"

#include <algorithm>

#include "Character.h"

Combat::Combat(Creature *c)
{
    instigator = c;
    firstAttacked = NULL;
    
    participants = new vector<Creature*>;
    
    turnSequence = new vector<Creature*>;
    currentTurn = 0;
    
    isFirstTurn = true;
}

Combat::~Combat()
{
    if ( participants )
        delete participants;
    
    if ( turnSequence )
        delete turnSequence;
}

void Combat::AddToCombat(Creature *c)
{
    // TODO: Check if already in list of participants
    participants->push_back(c);
}

void Combat::RemoveFromCombat(Creature *c)
{
    // Search for it, remove if found
    vector<Creature*>::iterator it = std::find(participants->begin(), participants->end(), c);
    
    // TODO: Maybe throw exception if not found?
    if ( it != participants->end() )
    {
        participants->erase(it);
        
        // Remember to remove from turn sequence
        
        // Find the removed creature in the sequence
        vector<Creature*>::iterator its = std::find(turnSequence->begin(), turnSequence->end(), c);
        turnSequence->erase(its);
    }
}

// Predicate method for turn sequence sorting
// Compares creature sequence values
bool sequenceSortPredicate(Creature *a, Creature *b)
{
    // Access stored value instead of recomputing
    // The other classes are responsible for updating these whenever something changes
    
    // Use > since higher values go first
    return (a->sequence > b->sequence);
}


// Sort the active participants by turn
// This is done every time each has taken a turn and is determined by the sequence stat
// However when combat is started, the instigator always gets to go first.
// Whoever is _attacked_ first then gets to go second. Afterwards, turns progress by sequence.
void Combat::SortTurnSequence()
{
    if ( isFirstTurn )
    {
        // only add instigator, record who he attacked for next creature to go
        turnSequence->clear();
        turnSequence->push_back(instigator);
        currentTurn = 0;
        
        // TODO:
        // Get second to go, push it back
    }
    else
    {
        // Remove and reinsert all eligible creatures
        // We do this (though costly) since not all are in the list after the first turn
        // Also, we may allow creatures to "sit out" turns in the future if they are knocked out
        turnSequence->clear();
        turnSequence = participants;    // Deep copy of pointers, so it is really shallow
        
        // Sort based on sequence
        std::sort(turnSequence->begin(), turnSequence->end(), sequenceSortPredicate);
    }
}

// Either fall back to UI to get player action, or query creature AI for one.
void Combat::DoNextAction()
{
    // The creature to go
    // Constant access into dynamic list is shitty, I know :(. Too lazy to store iterators
    Creature *currCreature = turnSequence->at(currentTurn);
    
    // Is it a player or AI?
    if ( currCreature->type == EntityType::Player )
    {
        // downcast
        Character *player = dynamic_cast<Character*>(currCreature);
        
        
    }
    else
    {
        // Query AI for action
        
        // Wait for a short while after AI actions
        
    }
    
}

// Creature is done with their turn, so go to next or initiate next round
void Combat::NextTurn()
{
    // Not last to go? just let next one take over
    if ( currentTurn < turnSequence->size() )
    {
        currentTurn++;
    }
    else
    {
        // Can combat end naturally?
        
        
        // Otherwise initiate a new round
        SortTurnSequence();     // Get new turn sequence, order may have changed
        currentTurn = 0;
        
        // Just execute next one immediately
        DoNextAction();
    }
}

bool Combat::DoesCombatEndNaturally()
{
    // First the easy check: Is there only one combatant left?
    // Usually this is the player
    if ( participants->size() == 1 )
        return true;
    
    // Check disposition between every pair of combatants
    // If there is a single hostile one, we have to go on
    for ( auto it1 = participants->begin(); it1 != participants->end(); ++it1 )
        for ( auto it2 = participants->begin(); it2 != participants->end(); ++it2 )
        {
            // Same guy?
            if ( it1 == it2 )
                continue;
        }
    
    // If we fall through to here, there is no more hostility
    return true;
}



