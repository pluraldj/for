//
//  TopBarWindow.cpp
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


#include "TopBarWindow.h"
#include "Colors.h"

TopBarWindow::TopBarWindow(veci _topleft, veci _size) : Window(_topleft,_size,false)
{
    hp = hpmax = ap = apmax = caps = xp = level = 0;
    isRadiated = isPoisoned = false;
    
    Colors::DefaultPair->MakeActive(cursesWin);
    
    // TMP DEBUG
    /*
    init_color(100, 1000, 1000, 1000);
    init_color(101, 0, 0, 0);
    init_pair(100, 101, 100);
    
    init_pair(1,COLOR_GREEN,COLOR_RED);
     
    wcolor_set(cursesWin, 1, NULL);*/
}

void TopBarWindow::SetCaptions(string _pln, string _tit, string _loc, int _hp, int _hpm, int _ap, int _apm, int _cap, int _xp, int _lev, bool _cri, bool _rad, bool _poi)
{
    playername = _pln;
    title = _tit;
    location = _loc;
    hp = _hp;
    hpmax = _hpm;
    ap = _ap;
    apmax = _apm;
    caps = _cap;
    xp = _xp;
    level = _lev;
    isCrippled = _cri;
    isRadiated = _rad;
    isPoisoned = _poi;
}

void TopBarWindow::Redraw()
{
    // number of "points" to draw on HP bar
    const int nHpPoints = 15;
    
    Window::Redraw();
    
    // Top line
    wmove(cursesWin,0,0);
    
    wprintw(cursesWin, playername.c_str());

    if ( title != "" )
    {
        wprintw(cursesWin, " the ");
        wprintw(cursesWin, title.c_str());
    }
    
    int xpnext = Character::XpToNextLevel(level);
    
    wprintw(cursesWin, (" - Lvl " + numberToString(level) + " - XP " + numberToString(xp) + " (" + numberToString(xpnext) + ")").c_str());
    
    wprintw(cursesWin, (" - $" + numberToString(caps)).c_str());
    
    // Second line
    wmove(cursesWin,1,0);

    // hp percentage
    double hppd = ((double)hp)/((double)hpmax);
    int hppi = (int)round(hppd*100.0);
    
    // Number of filled points on HP bar
    int hpFilled = (int)round(hppd*nHpPoints);
    
    // if we're not dead, always show at least one
    if ( hp > 0 )
        hpFilled = max(1,hpFilled);
    
    wprintw(cursesWin, "HP ");
    
    wprintw(cursesWin, (numberToString(hp) + "/" + numberToString(hpmax) + " ").c_str());
    
    // HP bar
    
    // Color hp based on percentage
    // TODO
    
    wprintw(cursesWin, "[");
    for ( int i=0; i<hpFilled; ++i )
        wprintw(cursesWin, "X");
    for ( int i=hpFilled; i<nHpPoints; ++i )
        wprintw(cursesWin, " ");
    wprintw(cursesWin, "]");
    
    // Status markers
    if ( isCrippled || isRadiated || isPoisoned )
    {
        wprintw(cursesWin, " -");
    
        if ( isCrippled )
            wprintw(cursesWin, " *CRIPPLED*");
        
        if ( isRadiated )
            wprintw(cursesWin, " *RAD*");
        
        if ( isPoisoned )
            wprintw(cursesWin, " *POISON*");
    }
    
    // Third line
    wmove(cursesWin,2,0);
    
    wprintw(cursesWin, ( "AP " + numberToString(ap) + "/" + numberToString(apmax)+ " ").c_str());
    
    // AP bar
    
    wprintw(cursesWin, "[");
    for ( int i=0; i<ap; ++i )
        wprintw(cursesWin, "X");
    for ( int i=ap; i<apmax; ++i )
        wprintw(cursesWin, " ");
    wprintw(cursesWin, "]");
    
    wrefresh(cursesWin);
}

