//
//  RightMenuWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
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


#ifndef __forogue__RightMenuWindow__
#define __forogue__RightMenuWindow__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <algorithm>
#include <vector>

#include "Window.h"
#include "Action.h"
#include "Item.h"

enum class RightMode { None, Normal, Combat, Stats, Inventory };

class RightMenuWindow : public Window
{
public:
    RightMenuWindow(veci _topleft, veci _size);
    ~RightMenuWindow();
    
    // Add possible actions for mode
    void EnterMode( RightMode mode );
    
    // Clean up actions that are no longer possible when exiting mode
    void ExitMode( RightMode mode );
    
    void Redraw(int currSlot, Item* slot1, Item* slot2);
    
private:
    
    vector<Action*> availableActions;   // Actions available now
    void AddAction(Action* _a);
    void RemoveAction(Action *_a);
    
    // All possible actions
    Action *quit, *enterCombat, *exitCombat, *move, *moveCombat, *stats, *inventory, *inventoryCombat, *lookat;
};

#endif /* defined(__forogue__RightMenuWindow__) */
