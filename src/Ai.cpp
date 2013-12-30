//
//  Ai.cpp
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
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


#include "Ai.h"

Ai::Ai()
{
    mode = AiMode::Wander;
    attitude = AiAttitude::Hostile;
    canTalk = false;
    wantsToBarter = false;
}

bool Ai::WantsToFlee(int hp, int hpmax, vector<Creature*> combatParticipants)
{
    // TODO
    // For now, fight until death
    
    return false;
}

AiAction Ai::GetNextAction(Creature *us, Dungeon *dungeon)
{
    // TODO: Take environment into account
    
    // nothing in particular
    return AiAction::None;
}

AiCombatAction Ai::GetNextCombatAction(Creature *us, vector<Creature*> *combatants, Dungeon *dungeon)
{
    // TODO: Take other combatants into account
    // TODO: NPC on NPC combat
    // TODO: Ranged combat
    // TODO: Fleeing
    // TODO: Flee and end combat entirely
    
    // Close enough to player to attack? otherwise get close enough
    
    // Enough ap to attack?
    if ( us->AP <= 3 )
        return AiCombatAction::Attack;
    
    // Otherwise end turn
    return AiCombatAction::EndTurn;
}