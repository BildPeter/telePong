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
        speedBallMaxBasis_       = 12;
        speedBallMinBasis_       = 10;
        speedFactorPerRound = 1;
        roundOfGame_        = 1;
        verboseText_        = false;
    }
    ~PongGame();
    void                    setup( GeometryType *geometry, GameState &state, int ballSize );
    void                    update( ofRectangle bounds, list<CursorPoint> activeCursors );
    void                    draw();
    void                    startBall();
    void                    rescaleBounds();
    void                    setBallSpeed( int min, int max )        { speedBallMin_= min; speedBallMax_ = max; }
    void                    toggleVerbose( bool val )               { verboseText_ = val; }
    int                     getRound()                              { return roundOfGame_;}
    void                    setRounds( int rounds )                 { maxRoundsGame = rounds; }
    WinnerType              getWinner()                             { return winnerFinal; }
    ofPoint                 getBallPosition()                       { return ball_->getB2DPosition(); }
    std::pair<int, int>     getPointOfPlayer()                      { return std::make_pair( pointsLeft, pointsRight ); }
    
private:
    void                    rescaleBounds( ofRectangle bounds );
    void                    setAttractionLeft( int y, float amount );
    void                    setAttractionRight( int y, float amount );
    void                    updatePositions();
    void                    restrictSpeed(     shared_ptr< ofxBox2dRect > mBall, int maxRotSpeed );
    void                    catchBugVertical(  shared_ptr< ofxBox2dRect > mBall, double tolerance  );
    void                    resetBallAtBoundary( shared_ptr< ofxBox2dRect > mBall );
    void                    setCursorActiveCentered();
    void                    nextRound();
    void                    resetGame();
    void                    resetRound();

    
    void                    updateStartingGame();
    void                    updateRoundCountDown();
    void                    updateGameMovement();
    void                    updateAutoGame();
    
    bool                                    verboseText_;
    shared_ptr< ofxBox2dRect >              paddleLeft_, paddleRight_;
    GeometryType                           *geometries_;
    shared_ptr< ofxBox2dRect >              ball_;
    shared_ptr< ofxBox2d >                  world_;
    int                                     ballRadius_;
    int                                     speedBallMax_, speedBallMaxBasis_;
    int                                     speedBallMin_, speedBallMinBasis_;
    int                                     speedFactorPerRound;
    int                                     pointsLeft, pointsRight;
    WinnerType                              winnerLast, winnerFinal;
    list<CursorPoint>                       activeCursors_;
    list<CursorPoint>                       activeCursorsCentered_;
    GameState                              *stateOfGame_;
    int                                     roundOfGame_;
    int                                     maxRoundsGame;
    bool                                    startBall_;
};

}   // namespace telePong


#endif /* defined(__telePong__PongGame__) */
