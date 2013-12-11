//
//  Ai.cpp
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Ai.h"

Ai::Ai()
{
    mode = AiMode::Wander;
    attitude = AiAttitude::Neutral;
    canTalk = false;
    wantsToBarter = false;
}