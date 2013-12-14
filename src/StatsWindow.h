//
//  StatsWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 01/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__StatsWindow__
#define __forogue__StatsWindow__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

#include "Window.h"

class StatsWindow : public Window
{
public:
    StatsWindow(veci _topleft, veci _size);
    
private:
    // Data contained in window
};

#endif /* defined(__forogue__StatsWindow__) */
