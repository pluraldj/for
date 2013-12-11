//
//  Action.cpp
//  forogue
//
//  Created by Lasse Carstensen on 11/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Action.h"

Action::Action(UiAction _uiact, string _keyString, string _description, int _ap)
{
    uiAction = _uiact;
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