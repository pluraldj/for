//
//  StatsWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 01/12/13.
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


#ifndef __forogue__StatsWindow__
#define __forogue__StatsWindow__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

#include "Window.h"

#include "Character.h"

class StatsWindow : public Window
{
public:
    StatsWindow(veci _topleft, veci _size, Character *_chara);

    
    void Redraw();
    
private:
    Character *player;
};

#endif /* defined(__forogue__StatsWindow__) */
