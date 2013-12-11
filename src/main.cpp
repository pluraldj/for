//
//  main.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include <iostream>


#define _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <ncurses.h>
#include <menu.h>

#include <time.h>

#include "Game.h"
#include "Weapon.h"
#include "Ammo.h"
#include "Creature.h"
#include "Dungeon.h"
#include "Utils.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Seed RNG
    RNG *rnd = RNG::getInstance();
    rnd->seed((int)time(NULL));
    
    Game g = Game::getInstance();
    
    g.Init();
    
    while ( g.MainLoop() )
        ;
    
    return 0;
}