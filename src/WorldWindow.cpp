//
//  WorldWindow.cpp
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


#include "WorldWindow.h"

#include <curses.h>

WorldWindow::WorldWindow(veci _topleft, veci _size) : Window(_topleft,_size,true)
{
    loc = NULL;
    entities = NULL;
    playerVis = NULL;
    
    cam = veci(0,0);
}

void WorldWindow::SetLocation(Location *_l)
{
    loc = _l;
}

void WorldWindow::SetEntities(vector<Entity*> *ents)
{
    entities = ents;
}

void WorldWindow::SetVisInfo(Visibility *_vis)
{
    playerVis = _vis;
}

void WorldWindow::SetCamCenter(veci _cam)
{
    cam = _cam;
}

veci WorldWindow::GetCamCenter()
{
    return cam;
}

void WorldWindow::Redraw()
{
    Window::Redraw();
    
    if ( !loc )
        return;
    
    // upper left corner from cam coords
    veci ul = (veci)( (vecd)cam - 0.5*((vecd)(size)));
    
    // Background tiles
    
    // Size of window to draw (minus border)
    veci drawSize = size - veci(2,2);
    
    // Draw into string array
    wstring *lines = loc->drawRect(ul, drawSize, true, playerVis);
    
    // Draw line by line into window
    // Take box into account
    for ( int i=0; i<drawSize.y; i++ )
    {
        // Next line
        wmove(cursesWin,i+1,1);
        
        wstring ws = wstring(lines[i].begin(), lines[i].end());
        const wchar_t *wcstr = ws.c_str();
        waddwstr(cursesWin, wcstr);
        
        // OLD, does not respect wide chars
        //wprintw(cursesWin, lines[i].c_str());
    }
    
    // Delete temp. string array
    delete[] lines;
    
    // Entities on top of tiles
    for (auto it=entities->begin(); it != entities->end(); ++it )
    {
        veci entpos = (*it)->location;
        
        // Calculate position in window
        veci drawPos = entpos-ul;
        
        // Outside bounds?
        if ( drawPos.x < 0 || drawPos.x >= drawSize.x || drawPos.y < 0 || drawPos.y > drawSize.y)
            continue;
        
        wmove(cursesWin,drawPos.y+1, drawPos.x+1);
        
        wstring ws = (*it)->DrawSymbol();
        const wchar_t *wcstr = ws.c_str();
        waddwstr(cursesWin, wcstr);
    }

    wrefresh(cursesWin);
    
    attroff(COLOR_PAIR(1));
}
