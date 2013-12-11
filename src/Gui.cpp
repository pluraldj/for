//
//  Gui.cpp
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Gui.h"

Gui::Gui()
{
    // Children aren't allocated until call to Init()
    topBar = NULL;
    worldWindow = NULL;
    rightMenu = NULL;
    bottomWindow = NULL;
    
    mode = GuiMode::MainView;
    
    currSlot = 1;
    slot1 = NULL;
    slot2 = NULL;
    
    // Fill out keyboard key settings
    keyToActionMap[27] = UiAction::DoQuit;  // Can NEVER change, we need extra check for ESC
    
    // Movement, both menus and world
    keyToActionMap[KEY_LEFT] = UiAction::MoveLeft;
    keyToActionMap[KEY_RIGHT] = UiAction::MoveRight;
    keyToActionMap[KEY_UP] = UiAction::MoveUp;
    keyToActionMap[KEY_DOWN] = UiAction::MoveDown;
    
    // Open other screens
    // We need both upper and lower case as input is a text char
    keyToActionMap['c'] = UiAction::EnterExitCombat;
    keyToActionMap['C'] = UiAction::EnterExitCombat;
    keyToActionMap['i'] = UiAction::OpenInventory;
    keyToActionMap['I'] = UiAction::OpenInventory;
    
    keyToActionMap['l'] = UiAction::Inspect;
    keyToActionMap['L'] = UiAction::Inspect;
    
    keyToActionMap['m'] = UiAction::MoveCam;
    keyToActionMap['M'] = UiAction::MoveCam;
    
    keyToActionMap['o'] = UiAction::OpenContainer;
    keyToActionMap['O'] = UiAction::OpenContainer;
    
    keyToActionMap['t'] = UiAction::TalkTo;
    keyToActionMap['T'] = UiAction::TalkTo;
    
    keyToActionMap['b'] = UiAction::TalkTo;
    keyToActionMap['B'] = UiAction::TalkTo;
    
    
}

Gui::~Gui()
{
    // Destroy children
    if ( topBar )
        delete topBar;
    
    if ( worldWindow )
        delete worldWindow;
    
    if ( rightMenu )
        delete rightMenu;
    
    if ( bottomWindow )
        delete bottomWindow;
    
    // End ncurses
    endwin();
}

void Gui::Init()
{
    // Init locale for wide char printing
    // BEFORE initscr()
    setlocale(LC_CTYPE, "en_US.UTF-8");
    //setlocale(LC_CTYPE, "");
    
    // init ncurses
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    refresh();
    
    // Input timeout - return ERR if no input during tick
    timeout(100);
    
    // hide cursor
    curs_set(0);
    
    // Get term size
    getmaxyx(stdscr,scry,scrx);
    
    // Quit if not big enough
    if ( scrx < 40 || scry < 20 )
    {
        endwin();
        cout << "Your terminal is not big enough, resize it.\n";
        cout.flush();
        exit(0);
    }
    
    // Divide up screen real estate and init children
    
    // Top bar - height 2 across entire width with no border
    topBar = new TopBarWindow( veci(0,0), veci(scrx,2) );
    
    // Bottom bar takes up some %, minimum 3 height
    int h = max(scry/6,3);
    bottomWindow = new BottomWindow( veci(0,scry-h), veci(scrx,h), h-2 );
    
    // height of middle windows
    h = scry-h-2;
    
    // right bar takes up some %, minimum 20 width
    int w = max(scrx/5,20);
    
    worldWindow = new WorldWindow( veci(0,2), veci(scrx-w,h) );
    
    rightMenu = new RightMenuWindow( veci(scrx-w,2), veci(w,h) );
}

void Gui::SetDungeon(Dungeon *_d)
{
    if ( worldWindow )
        worldWindow->SetDungeon(_d);
}

void Gui::SetEntities(vector<Entity *> *_e)
{
    if ( worldWindow )
        worldWindow->SetEntities(_e);
}

void Gui::SetVisInfo(Visibility *_vis)
{
    if ( worldWindow )
        worldWindow->SetVisInfo(_vis);
}

void Gui::SetCamera(veci pos)
{
    worldWindow->SetCamCenter(pos);
}

void Gui::FocusOnChar(Character *ch)
{
    worldWindow->SetCamCenter(ch->location);
}

veci Gui::GetCamera()
{
    return worldWindow->GetCamCenter();
}

void Gui::MoveCamera(veci rel)
{
    worldWindow->SetCamCenter( worldWindow->GetCamCenter() + rel);
}

void Gui::Resize()
{
    // Get new term dims
    int newx,newy;
    
    getmaxyx(stdscr, newy, newx);
    
    // Same as before? Then no resizing
    if ( newx == scrx && newy == scry )
        return;
    
    // resize children
    // TODO
}

void Gui::PostMessage(string msg)
{
    bottomWindow->AddLine(msg);
}

void Gui::Redraw()
{
    // repaint children
    topBar->Redraw();
    worldWindow->Redraw();
    rightMenu->Redraw(currSlot, slot1, slot2);
    bottomWindow->Redraw();
}

void Gui::SetCharData(Character *chara, Location *loc)
{
    if ( !chara)
        return;
    
    // Extract information
    topBar->SetCaptions(chara->name, chara->title, loc->name, chara->currHP, chara->modHP, chara->currAP, chara->modAP, chara->caps, chara->XP, chara->level, false, false, false);
}

// Get input from keyboard.
// If it should be handled by the UI, do it
// Otherwise pass back to Game instance (movement etc.)
UiAction Gui::GetInput()
{
    // Block waiting for input (timeout specified earlier)
    int key = getch();
    
    // Nothing while we waited?
    if ( key == ERR )
        return UiAction::None;
    
    UiAction action = UiAction::None;
    
    // We need explicit check for ESC/ALT
    if ( key == 27 )
    {
        int otherkey = getch();
        if ( otherkey == ERR )
            action = UiAction::DoQuit;
    }
    else
    {
        // Look up corresponding action
        auto it = keyToActionMap.find(key);
        
        // No pair found? (unbound key)
        if ( it == keyToActionMap.end() )
            action = UiAction::None;
        else
            action = (*it).second;
    }
    
    return action;
}