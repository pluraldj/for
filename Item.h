//
//  Item.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Item__
#define __forogue__Item__

#include <iostream>
#include <string>

#include "Entity.h"

using namespace std;

class Item : public Entity
{
public:
    Item();
    virtual ~Item();
    
    int baseValue;
    int weight;
    
};


#endif /* defined(__forogue__Item__) */
