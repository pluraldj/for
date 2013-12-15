//
//  XmlParser.h
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
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


#ifndef __forogue__XmlParser__
#define __forogue__XmlParser__

#define _XOPEN_SOURCE_EXTENDED

#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <string>
#include <stdexcept>

// Error codes
enum {
    ERROR_ARGS = 1,
    ERROR_XERCES_INIT,
    ERROR_PARSE,
    ERROR_EMPTY_DOCUMENT
};

class XmlParser
{
public:
    XmlParser();
    virtual ~XmlParser();

    
protected:
    // Recursively traverse XML tree until a node with a certain tag is found
    // Returns NULL if none are found
    xercesc::DOMNode* FindFirstTag(xercesc::DOMNode *start, XMLCh *tag);
    
    // Parse DOM so it is ready to be traversed
    void ReadFile(std::string);
    
    // Parser and root document
    xercesc::XercesDOMParser *xercesParser;
    xercesc::DOMDocument *xmlDoc;
    
    // Internal class use only. Hold Xerces data in UTF-16 SMLCh type.
    XMLCh* TAG_root;
    XMLCh* TAG_ApplicationSettings;
    XMLCh* ATTR_OptionA;
    XMLCh* ATTR_OptionB;
};

#endif /* defined(__forogue__XmlParser__) */
