//
//  PongGame.h
//  telePong
//
//  Created by Peter A. Kolski on 03.05.15.
//
//

#ifndef __telePong__PongGame__
#define __telePong__PongGame__

#include <iostream>
#include "PongHelpers.h"
#include "ofxBox2d.h"

namespace telePong
{

class PongGame {
    
public:
    ~PongGame();
    void    setBoundaries( BoundaryType const &boundary )           { boundaries_ = boundary; }
    
    void restrictSpeed(     shared_ptr< ofxBox2dCircle > mBall, int maxSpeed );
    void catchBugVertical(  shared_ptr< ofxBox2dCircle > mBall );
    void resetBall(         shared_ptr< ofxBox2dCircle > mBall );
    void update();
    void draw();
    void init();
    void rescaleBounds();
    
    BoundaryType                            boundaries_;
    shared_ptr< ofxBox2dRect >             paddleLeft_, paddleRight_;
    shared_ptr< ofxBox2dCircle >           ball_;
    shared_ptr< ofxBox2d >                 world_;
};

}   // namespace telePong


#endif /* defined(__telePong__PongGame__) */
