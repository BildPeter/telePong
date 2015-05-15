//
//  PongIntermediate.cpp
//  telePong
//
//  Created by Peter A. Kolski on 15.05.15.
//
//

#include "PongIntermediate.h"

namespace telePong
{

void IntermediateControl::init()
{
    circleCenter_ = ofGetWindowRect().getCenter();
    ofTrueTypeFont::setGlobalDpi(72);
    
    fontVerdana.loadFont("verdana.ttf", 30, true, true);
    fontVerdana.setLineHeight(34.0f);
    fontVerdana.setLetterSpacing(1.035);
}
    
void IntermediateControl::update( ofRectangle world, list<CursorPoint> cursorList )
{
    worldDimension_  = world;
    cursorsAll_      = cursorList;
    
    switch (*stateOfGame_) {
        case AutoGame:
            updateAutoGame();
            break;
        case PlayerConfirmation:
            updatePlayerConfirmation();
            break;
            
        default:
            break;
    }
}
 
void IntermediateControl::draw()
{
    switch (*stateOfGame_) {
        case AutoGame:
            drawAutoGame();
            break;
        case PlayerConfirmation:
            drawPlayerConfirmation();
            break;
            
        default:
            break;
    }
}
    
// ------------------------------------------------------------------------

void IntermediateControl::updateAutoGame()
{
    for ( auto &cursor : cursorsAll_ )
    {
        if (cursor.position.distance( circleCenter_ ) < circleRadius_ ) {
            *stateOfGame_ = Playing;
        }
    }
}
    
void IntermediateControl::drawAutoGame()
{
    ofSetColor( ofColor::red );
    ofFill();
    ofCircle( circleCenter_, circleRadius_ );
    ofSetColor( ofColor::white );
    fontVerdana.drawString("Touch Me!", circleCenter_.x - 85, circleCenter_.y +10 );
}
    
// ------------------------------------------------------------------------

void IntermediateControl::updatePlayerConfirmation()
{
    
}
    
void IntermediateControl::drawPlayerConfirmation()
{
}

    
// ------------------------------------------------------------------------
    
}   // namespace telePong
