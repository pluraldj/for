//
//  CdkWindow.cpp
//  FOR
//
//  Created by Lasse Carstensen on 11/02/14.
//  Copyright (c) 2014 Lasse Carstensen. All rights reserved.
//

#include "CdkWindow.h"

CdkWindow::CdkWindow(veci _topleft, veci _size)
{
    topleft = _topleft;
    size = _size;
    
    visible = true;
    
    cursesWin = newwin(size.y, size.x, topleft.y, topleft.x);
    cdkScreen = initCDKScreen(cursesWin);
    
    // We want color
    //initCDKColor();
    
    Clear();
}

CdkWindow::~CdkWindow()
{
    Clear();
    
    destroyCDKScreen(cdkScreen);
    delwin(cursesWin);
}

void CdkWindow::Init()
{
}

bool CdkWindow::Resize(veci newtopleft, veci newsize)
{
    // TODO
    
    return true;
}

void CdkWindow::Redraw()
{
    boxWindow(cursesWin,0);
    drawShadow(cursesWin);
    refreshCDKScreen(cdkScreen);
}

void CdkWindow::Clear()
{
    eraseCDKScreen(cdkScreen);
}
