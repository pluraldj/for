//
//  TileSetParser.cpp
//  forogue
//
//  Created by Lasse Carstensen on 14/12/13.
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


#include "TileSetParser.h"
#include "TileSet.h"

#include <locale>

using namespace xercesc;

TileSetParser::TileSetParser()
{
}

TileSetParser::~TileSetParser()
{
}

DungeonTileType TileSetParser::StringToDungeonTileType(string str)
{
    if ( str == "outside" )
        return DungeonTileType::Outside;
    else if ( str == "floor" )
        return DungeonTileType::Floor;
    else if ( str == "wall" )
        return DungeonTileType::Wall;
    else if ( str == "sand" )
        return DungeonTileType::Sand;
    else if ( str == "grass" )
        return DungeonTileType::Grass;
    else if ( str == "water" )
        return DungeonTileType::Water;
    else
    {
        throw std::runtime_error("Unrecognized dungeon tile string " + str);
    }
}

WorldTileType TileSetParser::StringToWorldTileType(string str)
{
    if ( str == "dirt" )
        return WorldTileType::Dirt;
    else if ( str == "desert" )
        return WorldTileType::Desert;
    else if ( str == "grass" )
        return WorldTileType::Grass;
    else if ( str == "forest" )
        return WorldTileType::Forest;
    else if ( str == "ocean" )
        return WorldTileType::Ocean;
    else if ( str == "river" )
        return WorldTileType::River;
    else if ( str == "lake" )
        return WorldTileType::Lake;
    else if ( str == "ruins" )
        return WorldTileType::Ruins;
    else if ( str == "hilly" )
        return WorldTileType::Hilly;
    else if ( str == "mountains" )
        return WorldTileType::Mountains;
    else if ( str == "snowymountains" )
        return WorldTileType::SnowyMountains;
    else if ( str == "cave" )
        return WorldTileType::Cave;
    else if ( str == "traders" )
        return WorldTileType::Traders;
    else if ( str == "vault" )
        return WorldTileType::Vault;
    else if ( str == "camp" )
        return WorldTileType::Camp;
    else if ( str == "town" )
        return WorldTileType::Town;
    else
    {
        throw std::runtime_error("Unrecognized world tile string " + str);
    }
}

EntityType TileSetParser::StringToEntityType(string str)
{

    // TODO
    
    return EntityType::Player;
    
}

TileSet *TileSetParser::Load()
{
    // Default values to start with
    TileSet *result = new TileSet();
    
    // We want the default key/value pairs in the hashmaps as we're just overwriting any defined in XML
    // This way we keep default tiles for any not specified
    
    // Load (or fail spectacularly if not exist/syntax errors)
    ReadFile("data/tileset.xml");
    
    // Get the top-level element
    DOMElement* elementRoot = xmlDoc->getDocumentElement();
    
    if( !elementRoot )
        throw std::runtime_error( "Empty XML document!" );
    
    // Get possible types of tiles, not all need be defined
    DOMNodeList *worldTags = elementRoot->getElementsByTagName(TRANS("overworld"));
    DOMNodeList *dungeonTags = elementRoot->getElementsByTagName(TRANS("dungeon"));
    DOMNodeList *thingsTags = elementRoot->getElementsByTagName(TRANS("things"));
    
    // We skip if length of any is 0
    XMLSize_t numWorld = worldTags->getLength();
    XMLSize_t numDungeon = dungeonTags->getLength();
    XMLSize_t numThings = thingsTags->getLength();
    
    if ( numWorld == 1 )
    {
        // The node
        DOMNode *worldNode = worldTags->item(0);
        
        // Get attributes
        DOMNamedNodeMap *attr = worldNode->getAttributes();
        
        // Iterate over attributes and attempt to look them up
        XMLSize_t nattr = attr->getLength();
        for ( XMLSize_t a=0; a<nattr; ++a )
        {
            DOMNode *currAttr = attr->item(a);
            
            // Name and value
            string name = TRANS(currAttr->getNodeName());
            string val = TRANS(currAttr->getNodeValue());
            
            // Convert value to wide string for UTF8 characters
            std::wstring wval(val.size(), L' '); // Overestimate number of code points.
            wval.resize(mbstowcs(&wval[0], val.c_str(), val.size())); // Shrink to fit.
            
            // look up, ignore if exception thrown (name not found)
            /*
            WorldTileType wtt;
            try
            {
                wtt = StringToWorldTileType(name);
            }
            catch ( std::runtime_error &e )
            {
                continue;
            }
            
            result->worldSymbols[wtt] = ws;
             */
            
            // Actually, _don't_ catch the exception. We want to crash and burn if something's wrong
            // Just set it, if we get to here everything went ok
            WorldTileType wtt = StringToWorldTileType(name);
            result->worldSymbols[wtt] = wval;
        }
    }
    
    if ( numDungeon == 1 )
    {
        // The node
        DOMNode *dungeonNode = dungeonTags->item(0);
        
        // Get attributes
        DOMNamedNodeMap *attr = dungeonNode->getAttributes();
        
        // Iterate over attributes and attempt to look them up
        XMLSize_t nattr = attr->getLength();
        for ( XMLSize_t a=0; a<nattr; ++a )
        {
            DOMNode *currAttr = attr->item(a);
            
            // Name and value
            string name = TRANS(currAttr->getNodeName());
            string val = TRANS(currAttr->getNodeValue());
            
            // Convert value to wide string for UTF8 characters
            std::wstring wval(val.size(), L' '); // Overestimate number of code points.
            wval.resize(mbstowcs(&wval[0], val.c_str(), val.size())); // Shrink to fit.
            
            // Just set it, if we get to here everything went ok
            DungeonTileType dtt = StringToDungeonTileType(name);
            result->dungeonSymbols[dtt] = wval;
        }
    }
    
    if ( numThings == 1 )
    {
        // The node
        DOMNode *thingsNode = thingsTags->item(0);
        
        // Get attributes
        DOMNamedNodeMap *attr = thingsNode->getAttributes();
        
        // Iterate over attributes and attempt to look them up
        XMLSize_t nattr = attr->getLength();
        for ( XMLSize_t a=0; a<nattr; ++a )
        {
            DOMNode *currAttr = attr->item(a);
            
            // Name and value
            string name = TRANS(currAttr->getNodeName());
            string val = TRANS(currAttr->getNodeValue());
            
            // Convert value to wide string for UTF8 characters
            std::wstring wval(val.size(), L' '); // Overestimate number of code points.
            wval.resize(mbstowcs(&wval[0], val.c_str(), val.size())); // Shrink to fit.
            
            // Just set it, if we get to here everything went ok
            EntityType ett = StringToEntityType(name);
            result->entitySymbols[ett] = wval;
        }
    }
    
    return result;
}
















