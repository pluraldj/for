//
//  Action.cpp
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