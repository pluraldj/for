//
//  Combat.h
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

#ifndef __forogue__Combat__
#define __forogue__Combat__

#include <iostream>
#include <vector>

#include "Creature.h"

using namespace std;

// One instance of combat taking place.
// Only one active at a time, and one is instantiated when someone wants to initiate combat.
// This object keeps track of the participants, their actions, turn sequencing, conditions for ending (usually all opponents dead) and determines if it is possible for a participant to end combat by fleeing
// Combat can end with fleeing if you are far enough away from others to disengage or if all participants do not want to fight anymore.
// Usually combat only ends in death, either of the player or of all opponents.
class Combat
{
public:
    Combat(Creature *c);    // Takes pointer to combat instigator
    ~Combat();
    
    void AttemptJoin(Creature *c);  // Creature wants to fight, too!
    void AttemptFlee(Creature *c);  // Creature wants to get away!
    
    void AddToCombat(Creature *c);          // Someone new becomes hostile
    void RemoveFromCombat(Creature *c);     // No longer participating in combat, usually because they're dead
    
    void SortTurnSequence();
    
    // One creature takes an action.
    // Either from player input or from creature AI depending on creature type.
    // When out of AP or nothing more to do this turn, action is end turn
    void DoNextAction();
    
    void NextTurn();
    
    // Check if combat should expire naturally
    // This happens if no one is hostile towards each other anymore
    // Usually because all the hostile ones are dead!
    bool DoesCombatEndNaturally();
    
    // A single creature unilaterally decides to flee/cease hostilities
    // This is different from combat ending naturally, and only requires that
    // we can escape from the others (based on distance)
    bool AttemptCombatEnd(Creature *c);
    
private:
    Creature *instigator;               // First attacker and combat starter
    Creature *firstAttacked;            // First to get attacked, gets to go second
    
    // All participants
    vector<Creature*> *participants;
    
    // Participants sorted by turn sequence
    vector<Creature*> *turnSequence;
    int currentTurn;            // Index of creature with current turn
    
    bool isFirstTurn;       // Currently on suprise turn or regular turn?
};

#endif /* defined(__forogue__Combat__) */
