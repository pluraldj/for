//
//  Ammo.h
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


#ifndef __forogue__Ammo__
#define __forogue__Ammo__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>

#include "Item.h"

enum class AmmoType { AmmoNone,
    
    // Cartridges
    Cal_10mm,
    Cal_5mm,
    
    // Energy ammo
    SEC,    // small energy cell
    MFC     // microfusion cell
};

class Ammo : public Item
{
public:
    Ammo();
    ~Ammo();
    
    int rounds;
};

#endif /* defined(__forogue__Ammo__) */
