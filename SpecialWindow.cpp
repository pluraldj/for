//
//  SpecialWindow.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "SpecialWindow.h"

SpecialWindow::SpecialWindow(veci _topleft, veci _size) : Window(_topleft,_size,true)
{
    
}

SpecialWindow::~SpecialWindow()
{

}

void SpecialWindow::Redraw()
{
    Window::Redraw();
    
    wrefresh(cursesWin);
}