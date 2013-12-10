//
//  Window.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Window.h"

Window::Window(veci _topleft, veci _size, bool _hasBox)
{
    topleft = _topleft;
    size = _size;
    hasBox = _hasBox;
    
    visible = true;
    
    cursesWin = newwin(size.y, size.x, topleft.y, topleft.x);
    Clear();
}

Window::~Window()
{
    Clear();    // Get rid of drawn shit
    
    // Deallocate ncurses object
    delwin(cursesWin);
}

void Window::Clear()
{
    // delete border also
    //wborder(cursesWin,' ',' ',' ',' ',' ',' ',' ',' ');
    
    // HACKHACK: Clear windows properly with no flickering
    //wclear(cursesWin);
    
    //wrefresh(cursesWin);
}

// Draw only box if there is one - derived classes must do the rest
void Window::Redraw()
{
    // Don't draw hidden
    if ( !visible )
        return;
    
    Clear();
    
    if ( hasBox )
    {
        box(cursesWin,0,0);
    }
    
    //wrefresh(cursesWin);
}

// Dummy init - derived classes must reimplement
void Window::Init()
{
}

// Dummy IO - derived classes must reimplement
void Window::HandleKey(int keycode)
{
}