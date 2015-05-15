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
    
enum GameState{ AutoGame, Playing, GameOver };
    
public:
    PongGame()
    {
        ballRadius_         = 30;
        speedRestriction_   = 10;
        worldRect_          = ofGetWindowRect();
    }
    ~PongGame();
    void                    update();
    void                    draw();
    void                    init();
    void                    startBall();
    void                    rescaleBounds();
    void                    rescaleBounds( ofRectangle bounds );
    void                    setBoundaries( GeometryType    *geometry )      { geometries_       = geometry; }
    void                    setSpeedRestriction( int speed )                { speedRestriction_ = speed; }
    void                    setActivePoints( list<CursorPoint> cursorList ) { activeCursors_    = cursorList; }
    void                    setGameState( GameState state )                 { stateOfGame_      = state; }

    GameState               getGameState()                                  { return stateOfGame_; }
    
private:
    void                    setAttractionLeft( int y, float amount );
    void                    setAttractionRight( int y, float amount );
    void                    updatePositions();
    void                    restrictSpeed(     shared_ptr< ofxBox2dRect > mBall, int maxSpeed, int maxRotSpeed );
    void                    catchBugVertical(  shared_ptr< ofxBox2dRect > mBall, double tolerance  );
    void                    resetBall(         shared_ptr< ofxBox2dRect > mBall );
    
    shared_ptr< ofxBox2dRect >              paddleLeft_, paddleRight_;
    GeometryType                           *geometries_;
    shared_ptr< ofxBox2dRect >              ball_;
    shared_ptr< ofxBox2d >                  world_;
    ofRectangle                             worldRect_;
    int                                     ballRadius_;
    int                                     speedRestriction_;
    list<CursorPoint>                       activeCursors_;
    GameState                               stateOfGame_;
};

}   // namespace telePong


#endif /* defined(__telePong__PongGame__) */
