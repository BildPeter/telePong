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
    void                update( list<CursorPoint> cursorList );
    
    void                setGameStateGlobal( GameState &state )  { stateOfGame_ = &state; }
    void                setCircleRadius( float radius )         { circleRadius_ = radius; }
    void                toggleTextVerbose()                     { textVerbose_ = textVerbose_?false:true;}
    
private:
    void                drawAutoGame();
    void                drawPlayerConfirmation();
    void                updateAutoGame();
    void                updatePlayerConfirmation();
    void                resetPlayerConfirmation();
    
    bool                isPlayerOneConfirmed;
    bool                isPlayerTwoConfirmed;
    
    list<CursorPoint>   cursorsAll_;
    GameState          *stateOfGame_;
    ofPoint             circleCenter_;
    float               circleRadius_;
    ofRectangle         worldDimension_;
    ofTrueTypeFont      fontVerdana;
    GeometryType       *geometries_;
    bool                textVerbose_;
};
    
}   // namespace telePong

#endif /* defined(__telePong__PongIntermediate__) */
