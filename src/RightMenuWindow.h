//
//  RightMenuWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__RightMenuWindow__
#define __forogue__RightMenuWindow__

#include <iostream>
#include <algorithm>

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
