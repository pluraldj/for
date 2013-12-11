//
//  Action.h
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Action__
#define __forogue__Action__

#include <iostream>
#include <string>

#include "Utils.h"

using namespace std;

class Action
{
public:
    Action(unsigned int _key, string _keyString, string _description, int _ap);
    string Print();
    
private:
    unsigned int key;
    string keyString;
    string description;
    int ap;
};

#endif /* defined(__forogue__Action__) */
