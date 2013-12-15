//
//  Savefile.cpp
//  forogue
//
//  Created by Lasse Carstensen on 15/12/13.
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

#include "Savefile.h"
#include "Game.h"

#include <fstream>

const string Savefile::savePath = "savefile.dat";

Savefile::Savefile()
{
}

Savefile::~Savefile()
{
    // Destroy children
}

void Savefile::Save(GameState _g)
{
    // Open archive
    ofstream ofs(savePath.c_str());
    
    // Serialize recursively and save to archive
    boost::archive::text_oarchive oa(ofs);
    
    // DO IT
    oa << _g;
}

GameState Savefile::Load()
{
    GameState g;
    
    // Everything the opposite way compared to saving
    
    // Open archive, in this time
    ifstream ifs(savePath.c_str());
    
    // Serialize recursively and save to archive
    boost::archive::text_iarchive ia(ifs);
    
    // DO IT
    ia >> g;
    
    return g;
}

//
// Serializers
//
template<class Archive>
void serialize(Archive & ar, GameState & g, const unsigned int version)
{
    
}






