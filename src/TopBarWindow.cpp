//
//  TopBarWindow.cpp
//  forogue
//
//  Created by Lasse Carstensen on 30/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "TopBarWindow.h"

TopBarWindow::TopBarWindow(veci _topleft, veci _size) : Window(_topleft,_size,false)
{
    hp = hpmax = ap = apmax = caps = xp = level = 0;
    isRadiated = isPoisoned = false;
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
    
    // Second line
    wmove(cursesWin,1,0);

    // hp percentage
    double hppd = ((double)hp)/((double)hpmax);
    int hppi = (int)round(hppd*100.0);
    
    // Color hp based on percentage
    // TODO
    
    wprintw(cursesWin, ( "HP " + numberToString(hp) + "/" + numberToString(hpmax) + " [" + numberToString(hppi) + "%%]").c_str());
    wprintw(cursesWin, ( " - AP " + numberToString(ap) + "/" + numberToString(apmax)).c_str());
    wprintw(cursesWin, (" - $" + numberToString(caps)).c_str());
    
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
    
    wrefresh(cursesWin);
}

