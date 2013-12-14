//
//  Character.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

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
    
private:
};

#endif /* defined(__forogue__Character__) */
