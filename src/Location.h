//
//  Location.h
//  forogue
//
//  Created by Lasse Carstensen on 01/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Location__
#define __forogue__Location__

#include <iostream>
#include <string>

#include "Utils.h"
#include "Visibility.h"

using namespace std;

class Location
{
public:
    // Children must override and implement own drawing
    virtual string* drawRect(veci upperleft, veci window, bool fow, Visibility *vis) = 0;
    
    string name;
};

#endif /* defined(__forogue__Location__) */
