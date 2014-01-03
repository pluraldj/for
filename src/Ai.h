//
//  Ai.h
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


#ifndef __forogue__Ai__
#define __forogue__Ai__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>
#include <vector>

#include "Creature.h"
#include "Dungeon.h"
#include "Utils.h"

using namespace std;

// What an NPC is currently doing or wants to do
enum class AiMode
{
    AiModeNone,     // nothing in particular, just standing around
    Wander,         // Wander randomly around
    Attack,         // Wants to hurt the player
    Flee            // Wants to quit combat/escape certain death
};

// General disposition towards player/other NPCS
enum class AiAttitude {
    AttitudeNone,   // no disposition in particular
    Loving,
    Friendly,
    Neutral,
    Hostile,
    Aggressive
};

// Things we can do _out_ of combat
// Queried every (non-combat) turn from elsewhere
// After getting action we query what to do specifically, like where to move to
enum class AiAction
{
    None,
    Move,
    EnterCombat,
    Attack
};

// Things we can do _in_ combat
// Queried as long as its our turn during combat (from Combat instance)
// Like AiAction, afterwards we query for specific action, like who to attack with what weapon
enum class AiCombatAction
{
    None,
    Move,
    Attack,
    EndTurn,
    EndCombat,
    UseItem
};

// Every NPC has an AI object which determines how they react to situations.
class Ai
{
public:
    Ai();
    
    // Decide if we want to run
    // Based on health and what enemies we are facing in combat
    bool WantsToFlee(int hp, int hpmax, vector<Creature*> combatParticipants);
    
    // Query general action
    // These take pointers to creature since many creatures can share an Ai instance (similar behavior)
    AiAction GetNextAction(Creature *c, Dungeon *dungeon);
    AiCombatAction GetNextCombatAction(Creature *us, vector<Creature*> *combatants, Dungeon *dungeon);
    
    veci GetMoveDir();  // Relative vector with next move
    
    
    AiMode mode;
    AiAttitude attitude;
    bool canTalk;
    bool wantsToBarter;
    
    // Where we would like to move over a number of turns
    veci moveTarget;
};

#endif /* defined(__forogue__Ai__) */
