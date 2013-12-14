//
//  Ai.h
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Ai__
#define __forogue__Ai__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

using namespace std;

// What an NPC is currently doing or wants to do
enum class AiMode
{
    AiModeNone,   // nothing in particular
    Wander,
    Attack,
    Flee
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

// Every NPC has an AI object which determines how they react to situations.
class Ai
{
public:
    Ai();
    
    AiMode mode;
    AiAttitude attitude;
    bool canTalk;
    bool wantsToBarter;
};

#endif /* defined(__forogue__Ai__) */
