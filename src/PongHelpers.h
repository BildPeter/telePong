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
#include <set>

namespace telePong
{
    using namespace std;

struct BoundaryType
{
//    BoundaryType()
//    {
//        activeArea  = vector<ofRectangle>(2);
//        panels      = vector<ofRectangle>(2);
//    }
    
    std::vector<ofRectangle*>    activeArea;
    std::vector<ofRectangle*>    paddels;
};
    
    
}   // namespace telePong


#endif
