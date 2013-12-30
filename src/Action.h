//
//  Action.h
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


#ifndef __forogue__Action__
#define __forogue__Action__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <string>

#include "Utils.h"

using namespace std;

// Actions taken by players by pressing keys
// UI handles everything it can, these are passed back to Game object
enum class UiAction {
    None,
    
    Quit,
    
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    
    UseItem,
    DropItem,
    
    SwitchActiveSlot,
    FireWeapon,
    ReloadWeapon,
    
    OpenStats,
    OpenInventory,
    Inspect,
    MoveCam,
    
    EnterExitCombat,
    
    OpenContainer,
    TalkTo,
    BarterWith
};

// Container for action metadata displayed in the right-hand bar
class Action
{
public:
    Action(UiAction _uiact, string _keyString, string _description, int _ap);
    string Print();
    
private:
    UiAction uiAction;  // action to trigger when pressed
    string keyString;   // Key tp press
    string description; // Description of what action does
    int ap;             // AP cost, 0 for no cost (it is not printed)
};

#endif /* defined(__forogue__Action__) */
