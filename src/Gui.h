//
//  Gui.h
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


#ifndef __forogue__Gui__
#define __forogue__Gui__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>
#include <map>

#include <locale.h>
#include <ncurses.h>
#include <menu.h>

#include "Action.h"
#include "Window.h"
#include "TopBarWindow.h"
#include "WorldWindow.h"
#include "RightMenuWindow.h"
#include "BottomWindow.h"
#include "Colors.h"

using namespace std;

// Overarching UI mode - popups obscure the normal display
enum class GuiMode { Quit, CharCreation, MainView, StatsView, InventoryView, ContainerView, TradeView, BarterView, InspectView, CameraView };

class Gui
{
public:
    Gui();
    ~Gui();
    
    void Init();
    
    void SetLocation(Location *_l);
    void SetEntities(vector<Entity*> *_e);
    void SetVisInfo(Visibility *_vis);
    
    void SetCamera(veci pos);
    void FocusOnChar(Character *ch);
    veci GetCamera();
    void MoveCamera(veci rel);
    
    // Resize subwindows on terminal resize
    bool Resize();
    
    void Redraw();
    
    // Enter/exit modes and modify available actions accordingly
    void EnterMode(GuiMode _mode);
    void ExitMode(GuiMode _mode);
    
    // Write message in log
    void PostMessage(string msg);
    
    // Update top bar info about character
    void SetCharData(Character *chara, Location *loc);
    
    // Input
    UiAction GetInput();
    
private:
    // Divide screen real estate between the windows
    void DivideWindows();
    
    // Initialize ncurses color bindings
    void InitColors();
    
    int scrx, scry; // term dimensions
    
    bool floatActive;   // Any floating windows active on top of main view? (inventory etc.)
    
    // ncurses child windows for main view
    TopBarWindow *topBar;
    WorldWindow *worldWindow;
    RightMenuWindow *rightMenu;
    BottomWindow *bottomWindow;
    
    // Overarching GUI mode determines what info is presented and what actions are possible
    GuiMode mode;
    
    // Actions available in current mode
    vector<UiAction> possibleActions;
    
    // Items in quick-use slots
    int currSlot;
    Item *slot1;
    Item *slot2;
    
    // Mapping of key presses to actions
    map<int, UiAction> keyToActionMap;
};

#endif /* defined(__forogue__Gui__) */
