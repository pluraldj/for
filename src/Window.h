//
//  Window.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
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


#ifndef __forogue__Window__
#define __forogue__Window__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>

#include <locale.h>

#ifdef OSX
#include <ncurses.h>
#endif

#ifdef LINUX
#include <ncursesw/curses.h>
#endif

#include <menu.h>

#include "Utils.h"

class Window
{
public:
    Window(veci _topleft, veci _size, bool _hasBox);
    virtual ~Window();
    
    virtual void Init();
    
    bool Resize(veci newtopleft, veci newsize);
    virtual void Redraw();
    virtual void HandleKey(int keycode);
    void Clear();
    
    bool visible;
    bool hasBox;
    
protected:
    WINDOW *cursesWin;  // ncurses window object
    
    // dimensions of window
    veci topleft, size;
    
    // Dimensions of drawing area - excludes border if there is one
    veci drawTopleft, drawSize;
};

#endif /* defined(__forogue__Window__) */
