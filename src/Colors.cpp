//
//  Colors.cpp
//  forogue
//
//  Created by Lasse Carstensen on 26/12/13.
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

#include "Colors.h"

namespace Colors
{
    // Dum a table of terminal colors for debugging
    // Uses main curses window, must call this before creating others
    void colorTest()
    {
        move(0,0);
        
        for ( int i=0; i<LINES; ++i )
        {
            move(i,0);
            for ( int j=0; j<10; j++ )
            {
                // Get next color, set as background
                int id = i*10 + j;
                
                init_pair(10+id, 1, id);
                
                attron(COLOR_PAIR(10+id));
                addwstr(L"   ");
                attroff(COLOR_PAIR(10+id));
            }
        }
        
        refresh();
        
        
        getch();
        
        endwin();
        exit(0);
        
    }
    
    Color::Color()
    {
        cursesId = -1;
    }
    
    Color::Color(short _id)
    {
        cursesId = _id;
    }
    
    // Standard colors
    Color *Black = NULL;
    Color *White = NULL;
    Color *Green = NULL;
    Color *Blue = NULL;
    Color *Yellow = NULL;
    Color *Brown = NULL;
    Color *Gray = NULL;
    
    ColorPair::ColorPair()
    {
        foreground = White;
        background = Black;
        
        cursesId = -1;
    }
    
    ColorPair::ColorPair(Color *_fore, Color *_back)
    {
        foreground = _fore;
        background = _back;
        
        cursesId = -1;
    }
    
    void ColorPair::BindCursesId(short i)
    {
        cursesId = i;
        int result = init_pair(i, foreground->cursesId, background->cursesId);
    }
    
    void ColorPair::MakeActive(WINDOW *cursesWin)
    {
        // ID not bound yet? fail
        if ( cursesId == -1 )
            return;
        
        wcolor_set(cursesWin, cursesId, NULL);
    }
    
    void ColorPair::UseAsWindowBackground(WINDOW *cursesWin)
    {
        // ID not bound? do nothing
        if ( cursesId == -1 )
            return;
        
        wbkgd(cursesWin, COLOR_PAIR(cursesId));
    }
    
    // Standard color pairs
    ColorPair *DefaultPair = NULL;
    
    ColorPair *GreenOnBlack = NULL;
    ColorPair *BlueOnBlack = NULL;
    ColorPair *YellowOnBlack = NULL;
    ColorPair *BrownOnBlack = NULL;
    ColorPair *GrayOnBlack = NULL;
}