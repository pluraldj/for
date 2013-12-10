//
//  WeaponParser.h
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__WeaponParser__
#define __forogue__WeaponParser__

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>
#include <vector>
#include <algorithm>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "XmlParser.h"
#include "Weapon.h"

// Convert string to XmlCh*
#define TRANS(a) XMLString::transcode(a)

using namespace std;

class WeaponParser : public XmlParser
{
public:
    WeaponParser();
    ~WeaponParser();
    
    // XML string to type enum conversion methods
    WeaponType StringToWeaponType(string str);
    DamageType StringToDamageType(string str);
    AttackType StringToAttackType(string str);
    AmmoType StringToAmmoType(string str);
    
    vector<Weapon*> *Load();
    
private:
    vector<Weapon*> *weapons;
};

#endif /* defined(__forogue__WeaponParser__) */
