//
//  Utils.h
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__Utils__
#define __forogue__Utils__

#include <iostream>
#include <math.h>
#include <random>
#include <sstream>

using namespace std;

// Random numbers
class RNG
{
public:
    static RNG *getInstance()
    {
        static RNG inst;
        return &inst;
    }
    
    void seed(int s);
    
    int random_int(int upper);
    int random_int(int lower, int upper);
    
    double random_double();
    double random_double(double lower, double upper);
    
    int throwDie(int nsides, double *probs);
    
private:
    RNG(){}
    
    RNG(RNG const&);              // Don't Implement
    void operator=(RNG const&); // Don't implement
    
    std::mt19937 rng;
};

// 2D vectors
class vecd;

class veci
{
public:
    veci();
    veci(int _x, int _y);
    
    double length();
    
    operator vecd ();
    
    int x,y;
};

veci operator *(int s, veci a);
veci operator +(veci a, veci b);
veci operator -(veci a, veci b);
bool operator ==(veci a, veci b);
int dot(veci a, veci b);

class vecd
{
public:
    vecd();
    vecd(double _x, double _y);
    
    double length();
    
    operator veci ();
    
    double x,y;
};

vecd operator *(double s, vecd a);
vecd operator +(vecd a, vecd b);
vecd operator -(vecd a, vecd b);
double dot(vecd a, vecd b);

// rectangle intersection test
bool rectIntersect(veci top1, veci size1, veci top2, veci size2);

int stringToInt ( string str );
double stringToDouble( string str );
bool stringToBool( string str );

template <class T> string numberToString ( T number )
{
    ostringstream ss;
    ss << number;
    return ss.str();
}

#endif /* defined(__forogue__Utils__) */
