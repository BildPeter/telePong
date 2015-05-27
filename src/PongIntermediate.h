//
//  PongIntermediate.h
//  telePong
//
//  Created by Peter A. Kolski on 15.05.15.
//
//

#ifndef __telePong__PongIntermediate__
#define __telePong__PongIntermediate__

#include <iostream>
#include "PongHelpers.h"
#include "ofMain.h"

namespace telePong
{

class IntermediateControl{

public:
    void                setup( GeometryType *geometry );
    void                draw();
    void                update( list<CursorPoint> cursorList, int round, WinnerType winner );
    
    void                setGameStateGlobal( GameState &state )  { stateOfGame_ = &state; }
    void                toggleVerbose( bool val )               { verboseText_ = val; }
    void                setRasterPoints( int nr )               { rasterPoints_ = nr; }
    void                increaseRasterPointsIdle()              { rasterPoints_++; }
    void                decreaseRasterPointsIdle()              { if(rasterPoints_ > 0) rasterPoints_--; }
    
private:
    void                updateAutoGame();
    void                updatePlayerConfirmation();
    void                updateRoundCountDown();
    void                updateGameOver();

    void                drawAutoGame();
    void                drawPlayerConfirmation();
    void                drawRoundCountDown();
    void                drawPlaying();
    void                drawGameOver();
//    void                drawIdle();
    void                drawCalibartion();
    void                drawPlanB();

    void                resetPlayerConfirmation();
    void                resetGameOver();
    
    bool                isPlayerOneConfirmed;
    bool                isPlayerTwoConfirmed;
    

    unsigned int        rasterPoints_;
    list<CursorPoint>   cursorsAll_;
    GameState          *stateOfGame_;
//    ofPoint             circleCenter_;
//    float               circleRadius_;
    ofRectangle         worldDimension_;
    ofRectangle         rectGameOver;
    GeometryType       *geometries_;
    bool                verboseText_;
    int                 roundOfGame_;
    WinnerType          winner_;
    
    CountDown           countDownGameOver;
    CountDown           countDownPlaying;
    
    // TODO Flux
    ofTrueTypeFont      arcadeSmall;
	ofTrueTypeFont      arcadeMedium;
	ofTrueTypeFont      arcadeLarge;
	ofColor				colMagenta;
	ofColor				colBlue;
	ofColor				colGreen;
	ofColor				colWhite;
    ofImage             imageGameOverLeftWins, imageGameOverRightWins;
    ofImage             bgCountDown, bgIdle, bgPlaying, bgConfirmation;
    
    ofVideoPlayer       videoPlanB;
};
    
}   // namespace telePong

#endif /* defined(__telePong__PongIntermediate__) */
