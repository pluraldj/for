//
//  RightMenuWindow.cpp
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "RightMenuWindow.h"

RightMenuWindow::RightMenuWindow(veci _topleft, veci _size) : Window(_topleft,_size,true)
{
    availableActions.clear();
    
    // Set data for all actions
    quit = new Action(27, "Esc", "Quit",0);
    enterCombat = new Action('e', "E", "Enter combat",0);
    exitCombat = new Action('e', "E", "Exit combat",0);
    move = new Action(0,"Arrows", "Move", 0);
    moveCombat = new Action(0,"Arrows", "Move",1);
    stats = new Action('s', "S", "Player stats",0);
    inventory = new Action('i', "I", "Inventory",0);
    inventoryCombat = new Action('i',"I", "Inventory", 4);
    lookat = new Action('l', "L", "Look at",0);
    
    EnterMode(RightMode::RightNormal);
    EnterMode(RightMode::RightCombat);
}

RightMenuWindow::~RightMenuWindow()
{
    delete quit;
    delete enterCombat;
    delete exitCombat;
    delete move;
    delete moveCombat;
    delete stats;
    delete inventoryCombat;
    delete inventory;
    delete lookat;
}

void RightMenuWindow::AddAction(Action *_a)
{
    availableActions.push_back(_a);
}

void RightMenuWindow::RemoveAction(Action *_a)
{
    // Attempt to find it
    vector<Action*>::iterator it = std::find(availableActions.begin(),availableActions.end(), _a);
    
    // Not found? Doesn't matter, it's already gone
    if ( it == availableActions.end() )
        return;
    
    // Else remove it by iterator position
    availableActions.erase(it);
}

void RightMenuWindow::EnterMode(RightMode mode)
{
    switch ( mode )
    {
        case RightNone:
            availableActions.clear();
            break;
            
        case RightNormal:
            availableActions.clear();
            AddAction(quit);
            break;
            
        case RightCombat:
            RemoveAction(enterCombat);
            RemoveAction(inventory);
            RemoveAction(move);
            
            AddAction(exitCombat);
            AddAction(inventoryCombat);
            AddAction(moveCombat);
            break;
            
        case RightStats:
            break;
            
        case RightInventory:
            break;
    }
}

void RightMenuWindow::Redraw(int currSlot, Item *slot1, Item *slot2)
{
    Window::Redraw();
    
    int line=1;
    
    // Equipped items
    string slot1Str;
    if ( currSlot == 1 )
        slot1Str += "[X]";
    else
        slot1Str += "[ ]";
    
    slot1Str +=" Slot 1: ";
    if ( slot1 == NULL )
        slot1Str += "Empty";
    
    string slot2Str;
    if ( currSlot == 2 )
        slot2Str += "[X]";
    else
        slot2Str += "[ ]";
    
    slot2Str +=" Slot 2: ";
    if ( slot2 == NULL )
        slot2Str += "Empty";
    
    wmove(cursesWin,line,1);
    wprintw(cursesWin, slot1Str.c_str());
    line++;
    
    wmove(cursesWin,line,1);
    wprintw(cursesWin, slot2Str.c_str());
    line++;
    
    // Status
    
    // Print all actions
    line++;
    wmove(cursesWin, line, 1);
    wprintw(cursesWin, "Actions:");
    line++;
    for ( int i=0; i<availableActions.size(); ++i)
    {
        string toPrint = availableActions[i]->Print();
        
        wmove(cursesWin, line+i, 1);
        wprintw(cursesWin, toPrint.c_str());
    }
    
    wrefresh(cursesWin);
}