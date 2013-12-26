//
//  main.cpp
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


#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

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
    // This goes first just so we're really fucking sure it's done first
    // Init locale for wide char printing
    // BEFORE initscr()
    //setlocale(LC_CTYPE, "en_US.UTF-8");
    setlocale(LC_ALL, "");
    
    // Seed RNG
    RNG *rnd = RNG::getInstance();
    rnd->seed((int)time(NULL));
    
    Game *g = new Game();
    
    g->Init();
    
    while ( g->MainLoop() )
        ;
    
    delete g;
    
    return 0;
}