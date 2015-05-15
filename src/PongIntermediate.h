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
    void                init();
    void                draw();
    void                update( ofRectangle world, list<CursorPoint> cursorList );
    
    void                setGameStateGlobal( GameState &state )          { stateOfGame_ = &state; }
    void                setCircleRadius( float radius )                 { circleRadius_ = radius; }
    
private:
    void                drawAutoGame();
    void                updateAutoGame();
    list<CursorPoint>   cursorsAll_;
    GameState          *stateOfGame_;
    ofPoint             circleCenter_;
    float               circleRadius_;
    ofRectangle         worldDimension_;
    ofTrueTypeFont      fontVerdana;
};
    
}   // namespace telePong

#endif /* defined(__telePong__PongIntermediate__) */
