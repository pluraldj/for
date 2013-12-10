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

#define _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <ncurses.h>
#include <menu.h>

#include "Window.h"
#include "TopBarWindow.h"
#include "WorldWindow.h"
#include "RightMenuWindow.h"
#include "BottomWindow.h"

using namespace std;

// Overarching UI mode - popups obscure the normal display
enum GuiMode { CharCreation, Main, Stats, Inventory };

// Actions taken by players by pressing keys
// UI handles everything it can, these are passed back to Game object
enum UiAction { None, Quit, MoveLeft, MoveRight, MoveUp, MoveDown, OpenStats, OpenInventory, Inspect, MoveCam, EnterCombat, ExitCombat };

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
    
    GuiMode mode;
    
    // Actions available in current mode
    vector<UiAction> possibleActions;
};

#endif /* defined(__forogue__Gui__) */
