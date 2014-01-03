//
//  Gui.cpp
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


#include "Gui.h"

#include "TileSet.h"

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
    keyToActionMap[27] = UiAction::Quit;  // Can NEVER change, we need extra check for ESC
    
    // Movement, both menus and world
    keyToActionMap[KEY_LEFT] = UiAction::MoveLeft;
    keyToActionMap[KEY_RIGHT] = UiAction::MoveRight;
    keyToActionMap[KEY_UP] = UiAction::MoveUp;
    keyToActionMap[KEY_DOWN] = UiAction::MoveDown;
    
    // Items
    keyToActionMap['u'] = UiAction::UseItem;
    keyToActionMap['U'] = UiAction::UseItem;
    keyToActionMap['d'] = UiAction::DropItem;
    keyToActionMap['D'] = UiAction::DropItem;
    
    // TODO: Should change weapon firing to depend on attack modes
    keyToActionMap['f'] = UiAction::FireWeapon;
    keyToActionMap['F'] = UiAction::FireWeapon;
    keyToActionMap['r'] = UiAction::ReloadWeapon;   // May not be possible (wep uses no ammo)
    keyToActionMap['R'] = UiAction::ReloadWeapon;
    
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
    
    // Interact with environment (context sensitive)
    keyToActionMap['o'] = UiAction::OpenContainer;
    keyToActionMap['O'] = UiAction::OpenContainer;
    keyToActionMap['t'] = UiAction::TalkTo;
    keyToActionMap['T'] = UiAction::TalkTo;
    keyToActionMap['b'] = UiAction::BarterWith;
    keyToActionMap['B'] = UiAction::BarterWith;
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
    // Load tileset
    TileSet *tileset = TileSet::GetInstance();
    tileset->LoadFromFile("data/tileset.xml");
    
    // init ncurses
    initscr();
    
    // enable color output
    start_color();
    
    // setup input handling
    cbreak();
    keypad(stdscr, true);
    noecho();
    refresh();
    
    // Test if terminal supports colors at all
    if ( !has_colors() )
    {
        // TODO: Gentler error
        throw new std::runtime_error("Terminal does not support colors");
    }
    
    // Test that we can redefine colors as we like
    // The terminal must support it
    
    // CHANGED: For now, we just use built in colors
    // TODO: Uncomment if we're ever going to redefine colors
    //if ( !can_change_color() )
    //{
    //    // TODO: Gentler error
    //    throw new std::runtime_error("Terminal does not support redefining colors");
    //}
    
    // Initialize bindings from internal -> ncurses colors
    InitColors();
    
    // hide cursor
    curs_set(0);
    
    // Dump color table and exit
    Colors::colorTest();
    
    // Input timeout - return ERR if no input during tick
    timeout(100);
    
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
    // Initialise with dummy dimensions, then call DivideWindows() to get real dims
    topBar = new TopBarWindow( veci(0,0), veci(1,1) );
    bottomWindow = new BottomWindow( veci(0,0), veci(1,1), 0 );
    worldWindow = new WorldWindow( veci(0,0), veci(1,1) );
    rightMenu = new RightMenuWindow( veci(0,0), veci(1,1) );
    DivideWindows();
}

void Gui::DivideWindows()
{
    // TODO: Check if too small for proper display
    
    int h_top = 3;
    int h_bot = max(scry/8,3);
    int h_world = scry-h_top-h_bot;
    int w_right = max(scrx/3,24);
    int w_leftsub = scrx-w_right;
    
    rightMenu->Resize(veci(w_leftsub,0), veci(w_right,scry));
    
    topBar->Resize(veci(0,0), veci(w_leftsub,h_top));
    worldWindow->Resize(veci(0,h_top), veci(w_leftsub,h_world));
    bottomWindow->Resize(veci(0,h_top+h_world),veci(w_leftsub,h_bot));
    
    bottomWindow->SetScrollbackLines(h_bot);
}

void Gui::InitColors()
{
    // Instantiate single colors
    Colors::Black = new Colors::Color(0);
    Colors::White = new Colors::Color(255);
    
    Colors::Green = new Colors::Color(10);
    Colors::Blue = new Colors::Color(12);
    Colors::Yellow = new Colors::Color(11);
    Colors::Brown = new Colors::Color(130);
    Colors::Gray = new Colors::Color(244);
    
    // Instantiate pairs
    Colors::DefaultPair = new Colors::ColorPair(Colors::White, Colors::Black);
    
    Colors::GreenOnBlack = new Colors::ColorPair(Colors::Green, Colors::Black);
    Colors::BlueOnBlack = new Colors::ColorPair(Colors::Blue, Colors::Black);
    Colors::YellowOnBlack = new Colors::ColorPair(Colors::Yellow, Colors::Black);
    Colors::BrownOnBlack = new Colors::ColorPair(Colors::Brown, Colors::Black);
    Colors::GrayOnBlack = new Colors::ColorPair(Colors::Gray, Colors::Black);
    
    // Allocate IDs
    Colors::DefaultPair->BindCursesId(1);
    Colors::GreenOnBlack->BindCursesId(2);
    Colors::BlueOnBlack->BindCursesId(3);
    Colors::YellowOnBlack->BindCursesId(4);
    Colors::BrownOnBlack->BindCursesId(5);
    Colors::GrayOnBlack->BindCursesId(6);
}

void Gui::SetLocation(Location *_l)
{
    if ( worldWindow )
        worldWindow->SetLocation(_l);
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

// Attempt resizing if term dims changed.
// Returns true if resizing did happen, false otherwise
bool Gui::Resize()
{
    // Get new term dims
    int newx,newy;
    
    getmaxyx(stdscr, newy, newx);
    
    // Same as before? Then no resizing
    if ( newx == scrx && newy == scry )
        return false;
    
    // Save new dims
    scrx = newx;
    scry = newy;
    
    // resize children
    DivideWindows();
    
    // Redraw
    // Nope, caller should do this after calling Resize()
    
    return true;
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
            action = UiAction::Quit;
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