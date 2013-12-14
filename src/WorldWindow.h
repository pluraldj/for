//
//  WorldWindow.h
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__WorldWindow__
#define __forogue__WorldWindow__

#define _XOPEN_SOURCE_EXTENDED

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
