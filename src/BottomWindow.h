//
//  BottomWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__BottomWindow__
#define __forogue__BottomWindow__

#include <iostream>
#include <vector>
#include <string>

#include "Window.h"

using namespace std;

class BottomWindow : public Window
{
public:
    BottomWindow(veci _topleft, veci _size, int _msgLines);
    
    void AddLine(string msg);
    void ClearLines();
    
    void Redraw();
    
private:
    int msgLines;
    vector<string> scrollBack;
};

#endif /* defined(__forogue__BottomWindow__) */
