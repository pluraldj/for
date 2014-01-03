//
//  WorldWindow.h
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


#ifndef __forogue__WorldWindow__
#define __forogue__WorldWindow__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>

#include "Window.h"
#include "Dungeon.h"
#include "World.h"

class WorldWindow : public Window
{
public:
    WorldWindow(veci _topleft, veci _size);
    
    void SetLocation(Location *_l);
    void SetEntities(vector<Entity*> *ents);
    void SetVisInfo(Visibility *_vis);
    
    void SetCamCenter(veci _cam);
    veci GetCamCenter();
    
    void Redraw();
    
private:
    Visibility *playerVis;            // Visibility info for player char
    
    // Map to draw
    Location *loc;
    
    vector<Entity*> *entities;  // List of active entities in map
    veci cam;                   // Camera focus coords
};

#endif /* defined(__forogue__WorldWindow__) */
