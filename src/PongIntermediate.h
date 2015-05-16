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
#include "ofxTween.h"
#include "ofMain.h"

namespace telePong
{

class IntermediateControl{

public:
    void                setup( GeometryType *geometry );
    void                draw();
    void                update( list<CursorPoint> cursorList );
    
    void                setGameStateGlobal( GameState &state )  { stateOfGame_ = &state; }
    void                setCircleRadius( float radius )         { circleRadius_ = radius; }
    void                toggleTextVerbose()                     { verboseText_ = verboseText_?false:true;}
    
private:
    void                drawAutoGame();
    void                drawPlayerConfirmation();
    void                drawRoundCountDown();
    void                drawGameOver();
    void                updateAutoGame();
    void                updatePlayerConfirmation();
    void                updateRoundCountDown();
    void                updateGameOver();
    void                resetPlayerConfirmation();
    void                resetGameOver();
    
    bool                isPlayerOneConfirmed;
    bool                isPlayerTwoConfirmed;
    
    list<CursorPoint>   cursorsAll_;
    GameState          *stateOfGame_;
    ofPoint             circleCenter_;
    float               circleRadius_;
    ofRectangle         worldDimension_;
    ofTrueTypeFont      fontVerdana;
    GeometryType       *geometries_;
    bool                verboseText_;
    
    CountDown           countDownGameOver;
    CountDown           countDownPlaying;
};
    
}   // namespace telePong

#endif /* defined(__telePong__PongIntermediate__) */
