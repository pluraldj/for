//
//  BottomWindow.cpp
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


#include "BottomWindow.h"

BottomWindow::BottomWindow(veci _topleft, veci _size, int _msgLines) : Window(_topleft,_size,false)
{
    msgLines = 0;
    scrollBack = new deque<string>;
    
    SetScrollbackLines(_msgLines);
    
    // init scrollback lines to empty
    ClearLines();
}

BottomWindow::~BottomWindow()
{
    if ( scrollBack )
        delete scrollBack;
}

// Set number of lines shown in scrollback
// Called on resize
// Make sure to keep content if enlarged
void BottomWindow::SetScrollbackLines(int _msgLines)
{
    // No change in size? do nothing
    if ( _msgLines == msgLines )
        return;
    
    // Enlarging? add empty lines TO BACK
    if ( _msgLines > msgLines )
    {
        for ( int i=0; i < _msgLines-msgLines; i++ )
            scrollBack->push_back("");
    }
    // Removing, pop from FRONT
    else
    {
        for ( int i=0; i < _msgLines-msgLines; i++ )
            scrollBack->pop_front();
    }
    
    // Update for following calls
    msgLines = _msgLines;
}

void BottomWindow::AddLine(string msg)
{
    if ( scrollBack->empty() )
        return;
    
    // Pop top msg from top
    scrollBack->pop_front();
    
    // Push new on bottom
    scrollBack->push_back(msg);
    
    Redraw();
}

// Clear all, replace with empty
void BottomWindow::ClearLines()
{
    scrollBack->clear();
    
    for ( int i=0; i<msgLines; i++ )
        scrollBack->push_back("");
}

void BottomWindow::Redraw()
{
    Window::Redraw();
    
    // HACKHACK
    // Overwrite to clear old contents
    // You should really improve this!
    for ( int i=0; i<size.y; i++)
    {
        wmove(cursesWin, i,0);
        for ( int j=0; j<size.x; j++)
        {
            wprintw(cursesWin, " ");
        }
    }
    
    for ( int i=0; i<msgLines; i++ )
    {
        wmove(cursesWin, i,0);
        wprintw(cursesWin, scrollBack->at(i).c_str());
    }
    
    wrefresh(cursesWin);
}













