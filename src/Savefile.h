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

#include "Game.h"

using namespace std;

class Savefile;

// Wrapper for everything we need to load into Game instance
// As Game also initializes UI and other stuff we DON'T want to serialize
// we load the returned GameState object manually when returned from Load()
// This is just a dumb struct to be read from/written to
class GameState
{
public:
    GameState(){ g=NULL; }
    ~GameState(){}
    
    Game *g;
    
private:
    friend class Game;
    friend class Savefile;
    friend class boost::serialization::access;
};


// Serialization/deserialization of game state for saving/loading games
// As this is a roguelike, you don't get to save/load whenever you want!
// Serialization is recursive starting from main GameState instance
class Savefile
{
public:
    Savefile();
    ~Savefile();
    
    GameState Load();
    void Save(GameState _g);
    
private:
    // Static path to file
    static const string savePath;
    
    // Current savefile version for backwards compat.
    static const int currVersion = 1;
};

// Serializer functions
template<class Archive>
void serialize(Archive & ar, GameState & g, const unsigned int version);
template<class Archive>
void serialize(Archive & ar, Game & g, const unsigned int version);

#endif /* defined(__forogue__Savefile__) */
