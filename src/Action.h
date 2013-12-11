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
    BarterWith };

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
