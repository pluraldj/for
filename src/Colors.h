//
//  Colors.h
//  forogue
//
//  Created by Lasse Carstensen on 26/12/13.
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

#ifndef __forogue__Colors__
#define __forogue__Colors__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>

#include <locale.h>

#ifdef OSX
#include <ncurses.h>
#endif

#ifdef LINUX
#include <ncursesw/curses.h>
#endif

using namespace std;

namespace Colors
{
    void colorTest();
    
    class Color
    {
    public:
        Color();
        
        Color(short xtermId);   // From xterm 256 color palette
        
    private:
        friend class ColorPair;
        short cursesId;
    };
    
    // Statically defined standard colors
    extern Color *Black;
    extern Color *White;
    
    extern Color *Green;
    extern Color *Blue;
    extern Color *Yellow;
    extern Color *Brown;
    extern Color *Gray;
    
    class ColorPair
    {
    public:
        ColorPair();
        ColorPair(Color *_fore, Color *_back);
        
        Color *foreground;
        Color *background;
        
        void BindCursesId(short i);
        void MakeActive(WINDOW *cursesWin);
        void UseAsWindowBackground(WINDOW *cursesWin);
        
    private:
        short cursesId;
    };
    
    // Statically defined standard color pairs
    extern ColorPair *DefaultPair;
    
    extern ColorPair *GreenOnBlack;
    extern ColorPair *BlueOnBlack;
    extern ColorPair *YellowOnBlack;
    extern ColorPair *BrownOnBlack;
    extern ColorPair *GrayOnBlack;
    
};

#endif /* defined(__forogue__Colors__) */
