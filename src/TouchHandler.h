//
//  TouchHandler.h
//  telePong
//
//  Created by Peter A. Kolski on 09.05.15.
//
//

#ifndef __telePong__TouchHandler__
#define __telePong__TouchHandler__

#include <iostream>
#include "PongHelpers.h"
#include "ofxOsc.h"


namespace telePong
{

class TouchHandler{
public:
    void                update();
    void                setBoundaries( BoundaryType boundary )  { boundaries_ = boundary; }
    void                setupOSC( int port, string adress );
    ofxOscMessage       oscMessage_;
    
private:
    ofxOscReceiver      oscReciever_;
    BoundaryType        boundaries_;
    string              oscAdress_  = "";
    int                 oscPort_    = 3333;
};
    
}   // namespace telePong


#endif /* defined(__telePong__TouchHandler__) */
