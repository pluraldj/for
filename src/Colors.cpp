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
    Color::Color()
    {
        r=g=b=0;
        
        cursesId = -1;
    }
    
    Color::Color(int _r, int _g, int _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }
    
    void Color::BindCursesId(short i)
    {
        cursesId = i;
     
        short rc = ScaleToCursesValue(r);
        short gc = ScaleToCursesValue(g);
        short bc = ScaleToCursesValue(b);
        
        int result = init_color(i,rc,gc,bc);
    }
    
    short Color::ScaleToCursesValue(short c)
    {
        return (short)((double)c)*(1000.0/255.0);
    }
    
    
    // Standard colors
    Color *Black = NULL;
    Color *White = NULL;
    Color *Green = NULL;
    
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
    
    // Standard color pairs
    ColorPair *DefaultPair = NULL;
    ColorPair *GreenOnBlack = NULL;
}