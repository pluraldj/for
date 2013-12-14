//
//  SpecialWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__SpecialWindow__
#define __forogue__SpecialWindow__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

#include <menu.h>

#include "Window.h"
#include "Utils.h"

using namespace std;

class SpecialWindow : public Window
{
public:
    SpecialWindow(veci _topleft, veci _size);
    ~SpecialWindow();
    
    void Redraw();
};

#endif /* defined(__forogue__SpecialWindow__) */
