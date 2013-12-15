//
//  Armor.h
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
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


#ifndef __forogue__Armor__
#define __forogue__Armor__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

#include "Item.h"

struct DmgMods
{
public:
    DmgMods(){ DT=0; DR=0.0; }
    
    int DT;
    double DR;
};

class Armor : public Item
{
public:
    Armor();
    
    DmgMods normal;
    DmgMods laser;
    DmgMods fire;
    DmgMods plasma;
    DmgMods electrical;
    DmgMods explosive;
    DmgMods emp;
};

#endif /* defined(__forogue__Armor__) */
