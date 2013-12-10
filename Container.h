//
//  Container.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Container__
#define __forogue__Container__

#include <iostream>
#include <vector>

#include "Item.h"

using namespace std;

class Container
{
public:
    Container();
    ~Container();
    
    vector<Item*> contents;
};

#endif /* defined(__forogue__Container__) */
