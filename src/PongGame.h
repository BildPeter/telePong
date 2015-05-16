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
        roundOfGame         = 0;
        verboseText_        = false;
    }
    ~PongGame();
    void                    setup( GeometryType *geometry, GameState &state );
    void                    update( ofRectangle bounds, list<CursorPoint> activeCursors );
    void                    draw();
    void                    startBall();
    void                    rescaleBounds();
    void                    setSpeedRestriction( int speed )        { speedRestriction_ = speed; }
    void                    toggleTextVerbose()                     { verboseText_ = verboseText_?false:true;}
    
private:
    void                    rescaleBounds( ofRectangle bounds );
    void                    setAttractionLeft( int y, float amount );
    void                    setAttractionRight( int y, float amount );
    void                    updatePositions();
    void                    restrictSpeed(     shared_ptr< ofxBox2dRect > mBall, int maxSpeed, int maxRotSpeed );
    void                    catchBugVertical(  shared_ptr< ofxBox2dRect > mBall, double tolerance  );
    void                    resetBall(         shared_ptr< ofxBox2dRect > mBall );
    void                    nextRound();
    
    bool                                    verboseText_;
    shared_ptr< ofxBox2dRect >              paddleLeft_, paddleRight_;
    GeometryType                           *geometries_;
    shared_ptr< ofxBox2dRect >              ball_;
    shared_ptr< ofxBox2d >                  world_;
    int                                     ballRadius_;
    int                                     speedRestriction_;
    list<CursorPoint>                       activeCursors_;
    GameState                              *stateOfGame_;
    int                                     roundOfGame;
};

}   // namespace telePong


#endif /* defined(__telePong__PongGame__) */
