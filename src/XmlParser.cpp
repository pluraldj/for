//
//  XmlParser.cpp
//  forogue
//
//  Created by Lasse Carstensen on 09/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//


#include "XmlParser.h"

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

using namespace xercesc;
using namespace std;

/**
 *  Constructor initializes xerces-C libraries.
 *  The XML tags and attributes which we seek are defined.
 *  The xerces-C DOM parser infrastructure is initialized.
 */

XmlParser::XmlParser()
{
    xmlDoc = NULL;
    
    try
    {
        XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
    }
    catch( XMLException& e )
    {
        char* message = XMLString::transcode( e.getMessage() );
        cerr << "XML toolkit initialization error: " << message << endl;
        XMLString::release( &message );
        // throw exception here to return ERROR_XERCES_INIT
    }
    
    // Tags and attributes used in XML file.
    // Can't call transcode till after Xerces Initialize()
    TAG_root        = XMLString::transcode("root");
    TAG_ApplicationSettings = XMLString::transcode("ApplicationSettings");
    ATTR_OptionA = XMLString::transcode("option_a");
    ATTR_OptionB = XMLString::transcode("option_b");
    
    xercesParser = new XercesDOMParser;
}

/**
 *  Class destructor frees memory used to hold the XML tag and
 *  attribute definitions. It als terminates use of the xerces-C
 *  framework.
 */

XmlParser::~XmlParser()
{
    // Clean up
    delete xercesParser;
    
    try
    {
        XMLString::release( &TAG_root );
        
        XMLString::release( &TAG_ApplicationSettings );
        XMLString::release( &ATTR_OptionA );
        XMLString::release( &ATTR_OptionB );
    }
    catch( ... )
    {
        cerr << "Unknown exception encountered in TagNamesdtor" << endl;
    }
    
    // Terminate Xerces
    try
    {
        XMLPlatformUtils::Terminate();  // Terminate after release of memory
    }
    catch( xercesc::XMLException& e )
    {
        char* message = xercesc::XMLString::transcode( e.getMessage() );
        
        cerr << "XML toolkit teardown error: " << message << endl;
        XMLString::release( &message );
    }
}

void XmlParser::ReadFile(std::string path)
{
    
    // Test to see if the file is ok.
    struct stat fileStatus;
    
    errno = 0;
    if(stat(path.c_str(), &fileStatus) == -1) // ==0 ok; ==-1 error
    {
        if( errno == ENOENT )      // errno declared by include file errno.h
            throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
        else if( errno == ENOTDIR )
            throw ( std::runtime_error("A component of the path is not a directory."));
        else if( errno == ELOOP )
            throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
        else if( errno == EACCES )
            throw ( std::runtime_error("Permission denied."));
        else if( errno == ENAMETOOLONG )
            throw ( std::runtime_error("File can not be read\n"));
    }
    
    // Configure DOM parser.
    xercesParser->setValidationScheme( XercesDOMParser::Val_Never );
    xercesParser->setDoNamespaces( false );
    xercesParser->setDoSchema( false );
    xercesParser->setLoadExternalDTD( false );
    
    try
    {
        xercesParser->parse( path.c_str() );
        
        // no need to free this pointer - owned by the parent parser object
        xmlDoc = xercesParser->getDocument();
        
        // Get the top-level element
        DOMElement* elementRoot = xmlDoc->getDocumentElement();
        if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));
    }
    catch( xercesc::XMLException& e )
    {
        char* message = xercesc::XMLString::transcode( e.getMessage() );
        ostringstream errBuf;
        errBuf << "Error parsing file: " << message << flush;
        XMLString::release( &message );
    }
}


DOMNode* XmlParser::FindFirstTag(xercesc::DOMNode *start, XMLCh *tag)
{
    // Is this node good?
    if( start->getNodeType() &&  // true is not NULL
       start->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
    {
        DOMElement *startE = dynamic_cast<DOMElement*>(start);
        
        if ( XMLString::equals(startE->getTagName(), tag) )
        {
            return start;
        }
        
        // Nope, recursively search children.
        // If there aren't any, return NULL
        DOMNodeList* children = start->getChildNodes();
        XMLSize_t numc = children->getLength();
        
        if ( numc == 0 )
            return NULL;
        
        for( XMLSize_t xx = 0; xx < numc; ++xx )
        {
            DOMNode *child = children->item(xx);
            
            DOMNode* result = FindFirstTag(child, tag);
            
            // Did we score a hit?
            if ( result != NULL )
                return result;
            
            // Continue...
        }
        
        // No matching tag among children (recursively), so we failed.
        return NULL;
    }
    else
        return NULL;
}