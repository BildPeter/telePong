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

void IntermediateControl::setup( GeometryType *geometry )
{
    verboseText_    = false;
    circleRadius_   = 150;
    circleCenter_   = ofGetWindowRect().getCenter();
    geometries_     = geometry;
    ofTrueTypeFont::setGlobalDpi(72);
    
    fontVerdana.loadFont("verdana.ttf", 30, true, true);
    fontVerdana.setLineHeight(34.0f);
    fontVerdana.setLetterSpacing(1.035);
    
    resetPlayerConfirmation();
}
    
void IntermediateControl::update( list<CursorPoint> cursorList )
{
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
            *stateOfGame_ = PlayerConfirmation;
            if(verboseText_) { cout << "GameState: PlayerConfirmation\n";}
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
    for ( auto &cursor : cursorsAll_ ){
        if (!isPlayerOneConfirmed) {
            if ( ( cursor.side == left )&&(cursor.state == Paddle ) )
                isPlayerOneConfirmed = true;
        }
        if (!isPlayerTwoConfirmed) {
            if ( ( cursor.side == right )&&(cursor.state == Paddle ) )
                isPlayerTwoConfirmed = true;
        }
    }
    
    if ( isPlayerTwoConfirmed && isPlayerOneConfirmed) {
        resetPlayerConfirmation();
        *stateOfGame_ = Playing;
        if(verboseText_) { cout << "GameState: Playing\n";}
    }
}
    
void IntermediateControl::drawPlayerConfirmation()
{
    if (!isPlayerOneConfirmed) {
        ofSetColor( ofColor( 0, 255, 0, 100 ) );
        ofRect( *geometries_->activeArea[0] );
        ofPushMatrix();
        {
            ofSetColor( ofColor::white );
            string      _text   = "Player 1\nTouch Paddle";
            ofRectangle bounds  = fontVerdana.getStringBoundingBox(_text, 0, 0);
//            ofTranslate(bounds.width/2, bounds.height / 2, 0);
            ofRotateZ( 45 );
            fontVerdana.drawString(_text, bounds.width/2, bounds.height/2 );
            
            
//            fontVerdana.drawString("Player 1\nConfirm", (*geometries_).activeArea[0]->getCenter().x,
//                                   (*geometries_).activeArea[0]->getCenter().y);
        }
            ofPopMatrix();
    }
    if (!isPlayerTwoConfirmed) {
        ofSetColor( ofColor( 0, 255, 0, 100 ) );
        ofRect( *geometries_->activeArea[1] );
        ofSetColor( ofColor::white );
        fontVerdana.drawString("Player 2\nConfirm", (*geometries_).activeArea[1]->getCenter().x,
                                                    (*geometries_).activeArea[1]->getCenter().y);
    }
}
    
void IntermediateControl::resetPlayerConfirmation()
{
    isPlayerOneConfirmed = false;
    isPlayerTwoConfirmed = false;
}

    
// ------------------------------------------------------------------------
    
}   // namespace telePong
