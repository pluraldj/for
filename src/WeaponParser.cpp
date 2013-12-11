//
//  WeaponParser.cpp
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "WeaponParser.h"

using namespace xercesc;

WeaponParser::WeaponParser()
{
    weapons = NULL;
}

WeaponParser::~WeaponParser()
{
    // Do NOT delete list of items, we need them elsewhere.
    // They are the responsibility of the Game instance now
    //delete weapons;
}

WeaponType WeaponParser::StringToWeaponType(string str)
{
    if ( str == "melee" )
        return WeaponType::Melee;
    else if ( str == "smallgun" )
        return WeaponType::SmallGun;
    else if ( str == "biggun" )
        return WeaponType::BigGun;
    else if ( str == "energy" )
        return WeaponType::Energy;
    else if ( str == "thrown" )
        return WeaponType::Thrown;
    else if ( str == "explosive" )
        return WeaponType::Explosive;
    else if ( str == "unarmed" )
        return WeaponType::Unarmed;
    else
        throw "Unrecognized weapon type " + str;
}

AttackType WeaponParser::StringToAttackType(string str)
{
    if ( str == "single" )
        return AttackType::Single;
    else if ( str == "aimed" )
        return AttackType::Aimed;
    else if ( str == "burst" )
        return AttackType::Burst;
    else if ( str == "punch" )
        return AttackType::Punch;
    else if ( str == "swing" )
        return AttackType::Swing;
    else if ( str == "thrust" )
        return AttackType::Thrust;
    else if ( str == "throw" )
        return AttackType::Throw;
    else
        throw "Unrecognized attack type " + str;
}

DamageType WeaponParser::StringToDamageType(string str)
{
    if ( str == "normal" )
        return DamageType::Normal;
    else if ( str == "laser" )
        return DamageType::Laser;
    else if ( str == "fire" )
        return DamageType::Fire;
    else if ( str == "plasma" )
        return DamageType::Plasma;
    else if ( str == "electrical" )
        return DamageType::Electrical;
    else if ( str == "explosion" )
        return DamageType::Explosion;
    else if ( str == "emp" )
        return DamageType::EMP;
    else
        throw "Unrecognized damage type " + str;
}

AmmoType WeaponParser::StringToAmmoType(string str)
{
    if ( str == "10mm" )
        return AmmoType::Cal_10mm;
    else if ( str == "5mm" )
        return AmmoType::Cal_5mm;
    else if ( str == "sec" )
        return AmmoType::SEC;
    else if ( str == "mfc" )
        return AmmoType::MFC;
    else
        throw "Unrecognized ammo type " + str;
}

// Load all, fill in information and return alloc'ed list of prototypes
vector<Weapon*> *WeaponParser::Load()
{
    if ( weapons )
        delete weapons;
    
    weapons = new vector<Weapon*>;
    
    // Load (or fail spectacularly if not exist/syntax errors)
    ReadFile("data/weapons.xml");
    
    // Get the top-level element
    DOMElement* elementRoot = xmlDoc->getDocumentElement();
    
    if( !elementRoot )
        throw(std::runtime_error( "Empty XML document!" ));
    
    // Get weapon tags, first level below root
    DOMNodeList *weaponTags = elementRoot->getElementsByTagName(TRANS("weapon"));
    
    // Dummy check
    if ( !weaponTags )
        throw "Something went very wrong!";
    
    // Iterate over them
    XMLSize_t numw = weaponTags->getLength();
    
    for ( XMLSize_t w=0; w<numw; w++ )
    {
        Weapon *weap = new Weapon;  // To be filled out
        
        // Current node and element
        DOMNode* currWeapNode = weaponTags->item(w);
        DOMElement *currWeapElem = dynamic_cast<DOMElement*>(currWeapNode);
        
        // Get attribs
        DOMNamedNodeMap *attr = currWeapNode->getAttributes();
        
        weap->name = TRANS(attr->getNamedItem(TRANS("name"))->getNodeValue());
        
        // Read type as string and convert to enum type
        string typeStr = TRANS(attr->getNamedItem(TRANS("type"))->getNodeValue());
        weap->weaponType = StringToWeaponType(typeStr);
        
        // General item attributes
        weap->weight = stringToInt(TRANS(attr->getNamedItem(TRANS("weight"))->getNodeValue()));
        weap->baseValue = stringToInt(TRANS(attr->getNamedItem(TRANS("value"))->getNodeValue()));
        
        // Ammo if any
        DOMNodeList *ammoTags = currWeapElem->getElementsByTagName(TRANS("ammo"));
        
        // STUFF FUCKED UP??
        if ( ammoTags->getLength() > 1 )
            throw "Your XML is screwed up, son";
        
        if ( ammoTags->getLength() == 1 )
        {
            DOMNode *ammoNode = ammoTags->item(0);
            attr = ammoNode->getAttributes();
            
            string ammoTypeStr = TRANS(attr->getNamedItem(TRANS("type"))->getNodeValue());
            weap->ammoType = StringToAmmoType(ammoTypeStr);
            weap->ammoCapacity = stringToInt(TRANS(attr->getNamedItem(TRANS("capacity"))->getNodeValue()));
        }
        
        // Damage spec
        DOMNodeList *damageTags = currWeapElem->getElementsByTagName(TRANS("damage"));
        
        // STUFF FUCKED UP??
        if ( damageTags->getLength() != 1 )
            throw "Your XML is screwed up, son";
        
        DOMNode *dmgNode = damageTags->item(0);
        attr = dmgNode->getAttributes();
        
        typeStr = TRANS(attr->getNamedItem(TRANS("type"))->getNodeValue());
        weap->damageType = StringToDamageType(typeStr);
        weap->minDmg = stringToInt(TRANS(attr->getNamedItem(TRANS("min"))->getNodeValue()));
        weap->maxDmg = stringToInt(TRANS(attr->getNamedItem(TRANS("max"))->getNodeValue()));
        
        // Requirements if any
        DOMNodeList *reqsTags = currWeapElem->getElementsByTagName(TRANS("requirements"));
        
        // STUFF FUCKED UP??
        if ( reqsTags->getLength() > 1 )
            throw "Your XML is screwed up, son";
        
        if ( reqsTags->getLength() == 1 )
        {
            DOMNode *reqNode = reqsTags->item(0);
            attr = reqNode->getAttributes();
            
            DOMNode* strNode = attr->getNamedItem(TRANS("strength"));
            if ( strNode != NULL )
            {
                weap->strengthReq = stringToInt(TRANS(strNode->getNodeValue()));
            }
        }
        
        // Attack modes
        DOMNodeList *modesTags = currWeapElem->getElementsByTagName(TRANS("attackmode"));
        XMLSize_t nchild = modesTags->getLength();
        
        if ( nchild < 1 )
            throw "Must have at least one attack type.";
        
        for ( XMLSize_t m=0; m<nchild; m++ )
        {
            DOMNode *child = modesTags->item(m);
            
            AttackMode mode;
            attr = child->getAttributes();
            mode.name = TRANS(attr->getNamedItem(TRANS("name"))->getNodeValue());
            
            string typeStr = TRANS(attr->getNamedItem(TRANS("type"))->getNodeValue());
            mode.attackType = StringToAttackType(typeStr);
            
            // hmm
            
            mode.rounds = stringToInt(TRANS(attr->getNamedItem(TRANS("rounds"))->getNodeValue()));
            mode.apCost = stringToInt(TRANS(attr->getNamedItem(TRANS("ap"))->getNodeValue()));
            mode.range = stringToDouble(TRANS(attr->getNamedItem(TRANS("range"))->getNodeValue()));
            
            weap->attacks.push_back(mode);
        }
        
        weapons->push_back(weap);
    }
    
    return weapons;
}