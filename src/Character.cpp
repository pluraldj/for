//
//  Character.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Character.h"

Character::Character()
{
    type = EntityType::EntPlayer;
    
    modSpecial = baseSpecial;
    
    SetBaseStats();
    SetModdedStats();
    
    level=1;
    XP = 0;
    
    name = "VaultDweller";
    title = "Wanderer";
    
    caps = 0;
}

Character::~Character()
{
}

int Character::XpToNextLevel(int level)
{
    static int xpMult = 1000;
    
    return (level+1)*(level)/2*xpMult;
}

void Character::SetBaseStats()
{
    int ST = baseSpecial.strength;
    int PE = baseSpecial.perception;
    int EN = baseSpecial.endurance;
    int CH = baseSpecial.charisma;
    int IN = baseSpecial.intelligence;
    int AG = baseSpecial.agility;
    int LK = baseSpecial.luck;
    
    // Derived stats
    baseHP = 15 + 2*EN + ST;
    baseAP = 5 + floor(AG/2.0);
    baseAC = AG;
    baseCarry = (1+ST)*25;
    baseCritChance = ((double)LK)/100.0;
    baseDR = 0;
    baseHealRate = min( EN/3,1);
    baseMeleeDmg = min( ST - 5, 1);
    basePerkRate = 3;
    basePoisonResist = ((double)EN*5.0)/100.0;
    baseRadResist = ((double)EN*2.0)/100.0;
    baseSequence = 2*PE;
    baseSkillRate = 2*IN + 5;
    
    // SKILLS
    baseSkills.bigGuns = 10 + 1*AG;
    baseSkills.energyWeapons = 10 + 1*AG;
    baseSkills.meleeWeapons = 55 + 1*( (ST+AG)/2 );
    baseSkills.smallGuns = 35 + 1*AG;
    baseSkills.throwing = 40 + 1*AG;
    baseSkills.unarmed = 40 + 1*( (ST+AG)/2 );
    
    baseSkills.doctor = 15 + 1*( (IN+PE)/2 );
    baseSkills.firstAid = 30 + 1*( (IN+PE)/2 );
    baseSkills.lockpick = 20 + 1*( (PE+AG)/2 );
    baseSkills.repair = 20 + 1*IN;
    baseSkills.science = 25 + 2*IN;
    baseSkills.sneak = 25 + 1*AG;
    baseSkills.steal = 20 + 1*AG;
    baseSkills.traps = 20 + 1*( (AG+PE)/2 );
    
    baseSkills.barter = 20 + 2*CH;
    baseSkills.gambling = 20 + 3*LK;
    baseSkills.outdoorsman = 5 + 1*( (IN+EN)/2 );
    baseSkills.speech = 25 + 2*CH;
}

void Character::SetModdedStats()
{
    // Init to base values before modifying
    // TEMP, compute modded instead
    
    modSpecial = baseSpecial;
    modSkills = baseSkills;
    effectiveSkillPoints = modSkills;
    
    modHP = baseHP;
    modAP = baseAP;
    modAC = baseAC;
    modCarry = baseCarry;
    
    modCritChance = baseCritChance;
    modDR = baseDR;
    modHealRate = baseHealRate;
    modMeleeDmg = baseMeleeDmg;
    modPerkRate = basePerkRate;
    modPoisonResist = basePoisonResist;
    modRadResist = baseRadResist;
    modSequence = baseSequence;
    modSkillRate = baseSkillRate;
    
    
    // Bonuses from perks
    // TODO
    
    // Bonuses from items
    // TODO
}