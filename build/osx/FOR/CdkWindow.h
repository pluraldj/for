//
//  CdkWindow.h
//  FOR
//
//  Created by Lasse Carstensen on 11/02/14.
//  Copyright (c) 2014 Lasse Carstensen. All rights reserved.
//

#ifndef __FOR__CdkWindow__
#define __FOR__CdkWindow__

#include <iostream>

#include <cdk.h>

#include "Utils.h"

class CdkWindow
{
public:
    CdkWindow(veci _topleft, veci _size);
    virtual ~CdkWindow();
    
    virtual void Init();    // Children must reimplement
    
    bool Resize(veci newtopleft, veci newsize);
    
    virtual void Redraw();  // Children may reimplement
    
    void Clear();
    
    bool visible;
    
protected:
    // internal ncurses window handle
    WINDOW *cursesWin;
    
    // Internal CDK screen handle
    CDKSCREEN *cdkScreen;
    
    // position,size
    veci topleft, size;
};

#endif /* defined(__FOR__CdkWindow__) */
