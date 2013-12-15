//
//  SpecialWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
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
