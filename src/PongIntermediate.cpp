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
}
    
void IntermediateControl::draw()
{
    switch (*stateOfGame_) {
        case AutoGame:
            drawAutoGame();
            break;
            
        default:
            break;
    }
}

    
void IntermediateControl::update( ofRectangle world, list<CursorPoint> cursorList )
{
    worldDimension_     = world;
    cursorsAll_      = cursorList;
    
    switch (*stateOfGame_) {
        case AutoGame:
            updateAutoGame();
            break;
            
        default:
            break;
    }
}

void IntermediateControl::drawAutoGame()
{
    ofSetColor( ofColor::red );
    ofFill();
    ofCircle( circleCenter_, circleRadius_ );
    
}

void IntermediateControl::updateAutoGame()
{
    for ( auto &cursor : cursorsAll_ )
    {
        if (cursor.position.distance( circleCenter_ ) < circleRadius_ ) {
            *stateOfGame_ = Playing;
        }
    }
}
    
}   // namespace telePong
