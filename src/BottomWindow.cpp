//
//  BottomWindow.cpp
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "BottomWindow.h"

BottomWindow::BottomWindow(veci _topleft, veci _size, int _msgLines) : Window(_topleft,_size,false)
{
    msgLines = _msgLines;
    
    // init scrollback lines
    for ( int i=0; i<msgLines; i++ )
        scrollBack.push_back("");
}

void BottomWindow::AddLine(string msg)
{
    // Pop top msg from top
    scrollBack.erase(scrollBack.begin());
    
    // Push new on bottom
    scrollBack.push_back(msg);
    
    Redraw();
}

void BottomWindow::ClearLines()
{
    scrollBack.clear();
    
    for ( int i=0; i<msgLines; i++ )
        scrollBack.push_back("");
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
        wprintw(cursesWin, scrollBack.at(i).c_str());
    }
    
    wrefresh(cursesWin);
}













