//
//  RightMenuWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__RightMenuWindow__
#define __forogue__RightMenuWindow__

#include <iostream>

#include "Window.h"

class RightMenuWindow : public Window
{
public:
    RightMenuWindow(veci _topleft, veci _size);
    
    void Redraw();
};

#endif /* defined(__forogue__RightMenuWindow__) */
