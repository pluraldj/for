//
//  Utils.cpp
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


#include "Utils.h"

void RNG::seed(int s)
{
    rng.seed(s);
}

// Bewteen 0 and upper
int RNG::random_int(int upper)
{
    std::uniform_int_distribution<int32_t> dist(0,upper);
    
    return dist(rng);
}

// Between lower and upper
int RNG::random_int(int lower, int upper)
{
    std::uniform_int_distribution<int32_t> dist(lower,upper);
    
    return dist(rng);
}

// double between 0 and 1
double RNG::random_double()
{
    std::uniform_real_distribution<double> dist(0.0,1.0);
    return dist(rng);
}

// Throw a die to select an index from among a set of possible outcomes
// nsides is number of outcomes, probs is an array of length nsides with their associated probs
// all probabilities must add up to one
// returns the index into the array for the selected outcome
int RNG::throwDie(int nsides, double *probs)
{
    double d = random_double();
    
    double runningtotal = 0.0;
    
    for ( int i=0; i<nsides; i++ )
    {
        if ( runningtotal < d && d < runningtotal+probs[i] )
            return i;
        
        runningtotal += probs[i];
    }
    
    // Last one if none so far
    // This only happens if you fucked up and the probabilities do not add to one
    return nsides-1;
}

veci::veci()
{
    x=y=0;
}

veci::veci(int _x, int _y)
{
    x=_x;
    y=_y;
}

double veci::length()
{
    double dx = (double)x;
    double dy = (double)y;
    
    return sqrt( dx*dx + dy*dy );
}

veci::operator vecd()
{
    vecd result;
    result.x = (double)this->x;
    result.y = (double)this->y;
    
    return result;
}

veci operator *(int s, veci a)
{
    return veci(s*a.x, s*a.y);
}

veci operator +(veci a, veci b)
{
    return veci(a.x+b.x , a.y+b.y);
}

veci operator -(veci a, veci b)
{
    return veci(a.x-b.x , a.y-b.y);
}

bool operator ==(veci a, veci b)
{
    return a.x==b.x && a.y==b.y;
}

int dot(veci a, veci b)
{
    return a.x*b.x + a.y*b.y;
}

vecd::vecd()
{
    x=y=0;
}

vecd::vecd(double _x, double _y)
{
    x=_x;
    y=_y;
}

double vecd::length()
{
    return sqrt( x*x + y*y );
}

vecd::operator veci()
{
    veci result;
    result.x = (int)this->x;
    result.y = (int)this->y;
    
    return result;
}


vecd operator *(double s, vecd a)
{
    return vecd(s*a.x, s*a.y);
}

vecd operator +(vecd a, vecd b)
{
    return vecd(a.x+b.x , a.y+b.y);
}

vecd operator -(vecd a, vecd b)
{
    return vecd(a.x-b.x , a.y-b.y);
}

double dot(vecd a, vecd b)
{
    return a.x*b.x+a.y*b.y;
}

bool rectIntersect(veci top1, veci size1, veci top2, veci size2)
{
    veci tl1 = top1;
    veci br1 = top1+size1;
    
    veci tl2 = top2;
    veci br2 = top2+size2;
    
    return (    tl1.x <= br2.x &&
                tl2.x <= br1.x &&
                tl1.y <= br2.y &&
            tl2.y <= br1.y );
}


int stringToInt ( string str )
{
	return atoi(str.c_str());
}

double stringToDouble( string str )
{
	return atof(str.c_str());
}

bool stringToBool( string str )
{
	if ( str == "true" )
		return true;
	else if ( str == "false" )
		return false;
	else
		throw "Couldn't recognize string as boolean!";
}