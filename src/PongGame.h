//
//  PongGame.h
//  PongBox
//
//  Created by Peter A. Kolski on 03.05.15.
//
//

#ifndef __PongBox__PongGame__
#define __PongBox__PongGame__

#include <iostream>
#include "ofxBox2d.h"

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

#endif /* defined(__PongBox__PongGame__) */
