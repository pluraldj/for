//
//  XmlParser.h
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#ifndef __forogue__XmlParser__
#define __forogue__XmlParser__

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
