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
    PongGame()
    {
        ballRadius_         = 30;
        speedRestriction_   = 10;
        worldRect_          = ofGetWindowRect();
//        worldRect_          = ofRectangle( ofGetWindowRect().getPosition() , ofGetWindowWidth() + (ballRadius_*4), ofGetWindowHeight() );
    }
    ~PongGame();
    void update();
    void draw();
    void init();
    void rescaleBounds();
    void                    setBoundaries( BoundaryType    *boundary )      { boundaries_ = boundary; }
    vector<ofRectangle*>    &getPanels()                                     { return boundaries_->panels; }
    void                    setSpeedRestriction( int speed )                { speedRestriction_ = speed; }

    shared_ptr< ofxBox2dRect >              paddleLeft_, paddleRight_;
    
private:
    void updatePositions();
    void restrictSpeed(     shared_ptr< ofxBox2dCircle > mBall, int maxSpeed );
    void catchBugVertical(  shared_ptr< ofxBox2dCircle > mBall );
    void resetBall(         shared_ptr< ofxBox2dCircle > mBall );
    
    BoundaryType                           *boundaries_;

    shared_ptr< ofxBox2dCircle >            ball_;
    shared_ptr< ofxBox2d >                  world_;
    ofRectangle                             worldRect_;
    int                                     ballRadius_;
    int                                     speedRestriction_;

};

}   // namespace telePong


#endif /* defined(__telePong__PongGame__) */
