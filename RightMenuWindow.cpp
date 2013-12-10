//
//  RightMenuWindow.cpp
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "RightMenuWindow.h"

RightMenuWindow::RightMenuWindow(veci _topleft, veci _size) : Window(_topleft,_size,true)
{
}

void RightMenuWindow::Redraw()
{
    Window::Redraw();
    
    wrefresh(cursesWin);
}