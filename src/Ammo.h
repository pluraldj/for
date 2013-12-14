//
//  Ammo.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Ammo__
#define __forogue__Ammo__

#define _XOPEN_SOURCE_EXTENDED

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
