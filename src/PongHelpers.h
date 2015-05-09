//
//  PongHelpers.h
//  telePong
//
//  Created by Peter A. Kolski on 09.05.15.
//
//

#ifndef telePong_PongHelpers_h
#define telePong_PongHelpers_h

#include "ofMain.h"

namespace telePong
{
    
struct BoundaryType
{
    struct  data
    {
        ofRectangle     panelSize;
        ofRectangle     activeArea;
    };
    
    data    panelLeft;
    data    panelRight;
};
    
}   // namespace telePong


#endif
