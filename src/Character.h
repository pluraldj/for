//
//  Character.h
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


#ifndef __forogue__Character__
#define __forogue__Character__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "Entity.h"
#include "Special.h"
#include "Skills.h"
#include "Perk.h"
#include "Container.h"
#include "Trait.h"
#include "Visibility.h"

using namespace std;

class Character : public Entity
{
public:
    Character();
    ~Character();
    
    void SetBaseStats();
    void SetModdedStats();
    
    static int XpToNextLevel(int level);
    
    Special baseSpecial;
    Special modSpecial;
    
    Skills baseSkills;
    Skills modSkills;
    Skills addedSkillPoints;
    Skills effectiveSkillPoints;
    
    vector<Trait*> activeTraits;
    vector<Perk*> activePerks;
    
    class Container *inventory;
    
    Visibility *visInfo;
    
    // STATS
    int level;
    int XP;
    
    int baseHP;
    int modHP;
    int currHP;
    
    int baseAP;
    int modAP;
    int currAP;
    
    int baseAC;
    int modAC;
    
    int baseCarry;
    int modCarry;
    
    int caps;
    
    double baseCritChance;
    double modCritChance;
    
    int baseDR;
    int modDR;
    
    int baseHealRate;
    int modHealRate;
    
    int baseMeleeDmg;
    int modMeleeDmg;
    
    int basePerkRate;
    int modPerkRate;
    
    double basePoisonResist;
    double modPoisonResist;
    
    double baseRadResist;
    double modRadResist;
    
    int baseSequence;
    int modSequence;
    
    int baseSkillRate;
    int modSkillRate;
    
    string name;
    string title;
    
    // Kill counter
    // Type of creature killed and number of kills
    // Should sort by number of kills (max first)
    vector< pair<EntityType,int> > killsList;
    
private:
};

#endif /* defined(__forogue__Character__) */
