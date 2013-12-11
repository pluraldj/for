//
//  Window.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Window__
#define __forogue__Window__

#include <iostream>

#define _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <ncurses.h>
#include <menu.h>

#include "Utils.h"

class Window
{
public:
    Window(veci _topleft, veci _size, bool _hasBox);
    virtual ~Window();
    
    virtual void Init();
    
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
