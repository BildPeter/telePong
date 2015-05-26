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
    imageGameOverLeftWins.loadImage( "images/5_WIN_3.png" );
    imageGameOverRightWins.loadImage( "images/5_WIN_3_b.png" );

    bgIdle.loadImage("images/spielfeld_idle.png");
    bgConfirmation.loadImage("images/spielfeld_Confirmation.png");
    bgCountDown.loadImage("images/spielfeld_countdown.png");
    bgPlaying.loadImage("images/spielfeld_Playing.png");
    
    
    verboseText_            = false;
    rectGameOver            = ofRectangle(ofGetWidth()/2-200, ofGetHeight()/2-100, 400, 200);
//    circleRadius_           = 150;
//    circleCenter_           = ofGetWindowRect().getCenter();
    geometries_             = geometry;
    rasterPoints_           = 4;

    countDownPlaying.isSet  = false;
    countDownPlaying.max    = 5;
    countDownGameOver.isSet = false;
    countDownGameOver.max   = 10;
    
    ofTrueTypeFont::setGlobalDpi(72);
    fontVerdana.loadFont("PRESSSTART2P.TTF", 30, true, true);
    fontVerdana.setLineHeight(34.0f);
    fontVerdana.setLetterSpacing(1.035);
    
    resetPlayerConfirmation();
    resetGameOver();
}
    
void IntermediateControl::update( list<CursorPoint> cursorList, int round, WinnerType winner )
{
    cursorsAll_     = cursorList;
    roundOfGame_    = round;
    winner_         = winner;
    
    switch (*stateOfGame_) {
        case AutoGame:
            updateAutoGame();
            break;
        case PlayerConfirmation:
            updatePlayerConfirmation();
            break;
        case RoundCountDown:
            updateRoundCountDown();
            break;
        case GameOver:
            updateGameOver();
            break;
            
        default:
            break;
    }
}
 
void IntermediateControl::draw()
{
    switch (*stateOfGame_) {
//        case Idle:
//            drawIdle();
//            break;
        case Calibartion:
            drawCalibartion();
            break;
        case AutoGame:
            drawAutoGame();
            break;
        case PlayerConfirmation:
            drawPlayerConfirmation();
            break;
        case RoundCountDown:
            drawRoundCountDown();
            break;
        case Playing:
            drawPlaying();
            break;
        case GameOver:
            drawGameOver();
            break;
            
        default:
            break;
    }
}
    
void IntermediateControl::drawPlaying()
{
    ofSetColor( ofColor::white );
    bgPlaying.draw(0, 0);
}
    
// ------------------------------------------------------------------------
void IntermediateControl::drawCalibartion()
{
    ofSetColor( ofColor::red);
    ofFill();
    for (int mX = 0; mX < rasterPoints_; mX++) {
        for (int mY = 0; mY < rasterPoints_; mY++) {
            ofCircle(   (geometries_->world.getWidth()/rasterPoints_)*mX,
                        (geometries_->world.getHeight()/rasterPoints_)*mY, 5);
        }
    }
}
    
// ------------------------------------------------------------------------

void IntermediateControl::updateAutoGame()
{
    for ( auto &cursor : cursorsAll_ )
    {
        if ( rectGameOver.inside(  cursor.position ) ) {
            *stateOfGame_ = PlayerConfirmation;
            if(verboseText_) { cout << "GameState: PlayerConfirmation\n";}
        }
    }
}
    
void IntermediateControl::drawAutoGame()
{
    //TODO Flux
    ofSetColor( ofColor::fromHex( ofHexToInt( "e20074" ) ) );
    ofFill();
    ofRect( rectGameOver );
    ofSetColor( ofColor::white );
    fontVerdana.drawString("Touch\n Me", rectGameOver.position.x, rectGameOver.position.y );
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
        *stateOfGame_ = RoundCountDown;
        if(verboseText_) { cout << "GameState: RoundCountDown\n";}
    }
}
    
void IntermediateControl::drawPlayerConfirmation()
{
    ofSetColor( ofColor::white );
    bgConfirmation.draw(0, 0);
    
    if (!isPlayerOneConfirmed) {
        ofSetColor( ofColor( 0, 255, 0, 100 ) );
        ofRect( *geometries_->activeArea[0] );
        string      _text1   = "Player 1\nTouch Paddle";
        ofPushMatrix();
        {
            ofSetColor( ofColor::white );
            ofRectangle bounds  = fontVerdana.getStringBoundingBox(_text1, 0, 0);
            // Rotation point in the middle
            ofTranslate(bounds.width/2, bounds.height / 2, 0);
            // Flips X -> Y & Y -> -X
            ofRotateZ( 90 );
            fontVerdana.drawString(_text1, geometries_->world.getHeight()/2 - (bounds.width/2),
                                          -geometries_->activeArea[0]->getWidth() /2 + (bounds.height/2) + 30 );
        }
        ofPopMatrix();
    }
    if (!isPlayerTwoConfirmed) {
        string      _text2   = "Player 2\nTouch Paddle";
        ofSetColor( ofColor( 0, 255, 0, 100 ) );
        ofRect( *geometries_->activeArea[1] );
        ofPushMatrix();
        {
            ofSetColor( ofColor::white );
            ofRectangle bounds  = fontVerdana.getStringBoundingBox(_text2, 0, 0);
            ofTranslate(bounds.width/2, bounds.height / 2, 0);
            // Flips X -> -Y & Y -> X
            ofRotateZ( -90 );
            fontVerdana.drawString(_text2, -geometries_->world.getHeight()/2 - (bounds.width/2),
                                          + geometries_->world.getHeight() - geometries_->activeArea[1]->getWidth() - (bounds.height ) );
        }
        ofPopMatrix();
    }
}
    
void IntermediateControl::resetPlayerConfirmation()
{
    isPlayerOneConfirmed = false;
    isPlayerTwoConfirmed = false;
}
    
// ------------------------------------------------------------------------
void IntermediateControl::updateRoundCountDown()
{
    
    if (!countDownPlaying.isSet) {
        countDownPlaying.initialValue = ofGetElapsedTimef();
        countDownPlaying.isSet = true;
    }
    countDownPlaying.currentValue = countDownPlaying.max - ( ofGetElapsedTimef() - countDownPlaying.initialValue );
    
    if ( countDownPlaying.currentValue == 0)  {
        *stateOfGame_ = Playing;
        countDownPlaying.isSet = false;
    }
}

void IntermediateControl::drawRoundCountDown()
{
    ofSetColor( ofColor::white );
    bgCountDown.draw(0, 0);
    
    ofSetColor( ofColor::white );
    fontVerdana.drawString( "Round " + ofToString(roundOfGame_) + "\n\t"+ofToString(countDownPlaying.currentValue),
                           geometries_->world.getCenter().x, geometries_->world.getCenter().y +50);
}
    
// ------------------------------------------------------------------------
    
void IntermediateControl::updateGameOver()
{
    if (!countDownGameOver.isSet) {
        countDownGameOver.initialValue  = ofGetElapsedTimef();
        countDownGameOver.isSet         = true;
    }
    countDownGameOver.currentValue = countDownGameOver.max - ( ofGetElapsedTimef() - countDownGameOver.initialValue );
    
    if ( countDownGameOver.currentValue )
    {
        for ( auto &cursor : cursorsAll_ )
        {
            if ( rectGameOver.inside( cursor.position ) ) {
                *stateOfGame_ = RoundCountDown;
                if(verboseText_) { cout << "GameState: RoundCountDown\n";}
                resetGameOver();
            }
        }
    }else
    {
        *stateOfGame_ = AutoGame;
        resetGameOver();
    }
}

void IntermediateControl::drawGameOver()
{
    ofSetColor( ofColor::white );
    if (winner_ == Left) {
        imageGameOverLeftWins.draw(0,0);
    }else if (winner_ == Right)
    {
        imageGameOverRightWins.draw(0, 0);
    }
    ofSetColor( ofColor::fromHex( ofHexToInt("ffffff" ) ) );
    fontVerdana.drawString("Play again?\n" + ofToString(countDownGameOver.currentValue), rectGameOver.position.x, rectGameOver.position.y );
}
    
void IntermediateControl::resetGameOver()
{
    countDownGameOver.isSet = false;
}
    
    
    
// ------------------------------------------------------------------------
    
}   // namespace telePong
