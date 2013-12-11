//
//  Action.cpp
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Action.h"

Action::Action(unsigned int _key, string _keyString, string _description, int _ap)
{
    key = _key;
    keyString = _keyString;
    description = _description;
    ap = _ap;
}

string Action::Print()
{
    string toPrint = "[" + keyString + "]" + " " + description;
    
    if ( ap != 0 )
        toPrint += " (AP " + numberToString(ap) + ")";
    
    return toPrint;
}