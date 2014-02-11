//
//  Cave.h
//  FOR
//
//  Created by Lasse Carstensen on 10/02/14.
//  Copyright (c) 2014 Lasse Carstensen. All rights reserved.
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

#ifndef __FOR__Cave__
#define __FOR__Cave__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>

#include "Dungeon.h"
#include "DungeonArea.h"

class Cave : public Dungeon
{
public:
    Cave(DungeonSpec spec);
    ~Cave();
    
    // Create passage between areas
    void MakePassage(DungeonArea *A, DungeonArea *B);
    
    // Create passage between tiles (straight-through)
    void MakePassage(vecd A, vecd B);
    
    // Player spawn coords on entry
    veci GetPlayerSpawnCoords();
    
private:
    // Generate the fucker
    void Generate(DungeonSpec spec);
    
};



#endif /* defined(__FOR__Cave__) */
