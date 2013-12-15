//
//  Savefile.h
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

#ifndef __forogue__Savefile__
#define __forogue__Savefile__

#include <iostream>
#include <string>

// Boost serialization lib
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

class Game;

// Wrapper for everything we need to load into Game instance
// As Game also initializes UI and other stuff we DON'T want to serialize
// we load the returned GameState object manually when returned from Load()
class GameState
{
public:
    
    
    
private:
    friend class boost::serialization::access;
    
    // Serialization function
    // Operator & is << or >> depending on if we're going out/in
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        
    }
};


// Serialization/deserialization of game state for saving/loading games
// As this is a roguelike, you don't get to save/load whenever you want!
// Serialization is recursive starting from main GameState instance
class Savefile
{
public:
    Savefile();
    ~Savefile();
    
    GameState *Load();
    void Save(GameState *_g);
    
private:
    static const string savePath;
};

#endif /* defined(__forogue__Savefile__) */
