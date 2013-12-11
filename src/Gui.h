//
//  Gui.h
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Gui__
#define __forogue__Gui__


#include <iostream>
#include <map>

#define _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <ncurses.h>
#include <menu.h>

#include "Action.h"
#include "Window.h"
#include "TopBarWindow.h"
#include "WorldWindow.h"
#include "RightMenuWindow.h"
#include "BottomWindow.h"

using namespace std;

// Overarching UI mode - popups obscure the normal display
enum GuiMode { Quit, CharCreation, MainView, StatsView, InventoryView, ContainerView, TradeView, BarterView, InspectView, CameraView };

class Gui
{
public:
    Gui();
    ~Gui();
    
    void Init();
    
    void SetDungeon(Dungeon *_d);
    void SetEntities(vector<Entity*> *_e);
    void SetVisInfo(Visibility *_vis);
    
    void SetCamera(veci pos);
    void FocusOnChar(Character *ch);
    veci GetCamera();
    void MoveCamera(veci rel);
    
    // Resize subwindows on terminal resize
    void Resize();
    
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
