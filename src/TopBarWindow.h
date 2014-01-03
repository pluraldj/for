//
//  TopBarWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
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


#ifndef __forogue__TopBarWindow__
#define __forogue__TopBarWindow__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

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
