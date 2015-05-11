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
    

template< int size  = 2 >
struct BoundaryType
{
    BoundaryType()
    :   activeArea( size ),
        panels( size )
    {}
    
    vector<ofRectangle>     activeArea;
    vector<ofRectangle>     panels;
};
    
}   // namespace telePong


#endif
