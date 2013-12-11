//
//  TopBarWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__TopBarWindow__
#define __forogue__TopBarWindow__

#include <iostream>
#include <string>

#include "Window.h"
#include "Character.h"

using namespace std;

class TopBarWindow : public Window
{
public:
    TopBarWindow(veci _topleft, veci _size);
    
    void SetCaptions(string _pln, string _tit, string _loc, int _hp, int _hpm, int _ap, int _apm, int _cap, int _xp, int _lev, bool _crip, bool _rad, bool _poi);
    
    void Redraw();
    
private:
    string playername;
    string title;
    string location;
    
    int hp;
    int hpmax;
    
    int ap;
    int apmax;
    
    int caps;
    int xp;
    int level;
    
    bool isCrippled;
    bool isRadiated;
    bool isPoisoned;
};

#endif /* defined(__forogue__TopBarWindow__) */
