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
#include "ofxBox2d.h"

namespace telePong
{

class PongGame {
    
public:
    ~PongGame();
    void restrictSpeed(     shared_ptr< ofxBox2dCircle > mBall, int maxSpeed );
    void catchBugVertical(  shared_ptr< ofxBox2dCircle > mBall );
    void resetBall(         shared_ptr< ofxBox2dCircle > mBall );
    void update();
    void draw();
    void init();
    void rescaleBounds();
    
    shared_ptr< ofxBox2dRect >             paddleLeft, paddleRight;
    shared_ptr< ofxBox2dCircle >           ball;
    shared_ptr< ofxBox2d >                 world;
};

}   // namespace telePong


#endif /* defined(__telePong__PongGame__) */
