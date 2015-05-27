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
    countDownGameOver.max   = 5;
    
    ofTrueTypeFont::setGlobalDpi(72);

	// for information, like scores or notifications
	arcadeSmall.loadFont("PRESSSTART2P.TTF", 46, true, true);
    arcadeSmall.setLineHeight(49.0f);
    arcadeSmall.setLetterSpacing(1.035);

	// for rounds and announcements
	arcadeMedium.loadFont("PRESSSTART2P.TTF", 69, true, true);
    arcadeMedium.setLineHeight(72.0f);
    arcadeMedium.setLetterSpacing(1.035);

	arcadeLarge.loadFont("PRESSSTART2P.TTF", 189, true, true);
    arcadeLarge.setLetterSpacing(1.035);

	colWhite = ofColor::fromHex( ofHexToInt("ffffff" ) );
	colBlue = ofColor::fromHex( ofHexToInt("64b9e4" ) );
	colGreen = ofColor::fromHex( ofHexToInt("babd5a" ) );
	colMagenta = ofColor::fromHex( ofHexToInt("e20074" ) );
    
    resetPlayerConfirmation();
    resetGameOver();
    
    videoPlanB.loadMovie("movies/logoloop.mp4");
    videoPlanB.setLoopState(OF_LOOP_NORMAL);
    videoPlanB.play();
}
    
void IntermediateControl::update( list<CursorPoint> cursorList, int round, WinnerType winner )
{
    if ( *stateOfGame_ == PlanB)
    {
		videoPlanB.update();
        videoPlanB.setPaused( false );
    }else
    {
        videoPlanB.setPaused( true );
        
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
}
 
void IntermediateControl::draw()
{
    if ( *stateOfGame_ == PlanB)
    {
        drawPlanB();
    }else
    {
        switch (*stateOfGame_)
        {
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
}
    
void IntermediateControl::drawPlaying()
{
    ofSetColor( ofColor::white );
    bgPlaying.draw(0, 0);
	ofSetColor( colBlue );
	arcadeSmall.drawString("1", ofGetWidth() / 2 - 70, 100 );
	ofSetColor( colGreen );
	arcadeSmall.drawString("2", ofGetWidth() / 2 + 30, 100 );
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
    ofSetColor( colMagenta );
    ofFill();
    ofRect( rectGameOver );
    ofSetColor( colWhite );
    arcadeMedium.drawString("TOUCH\n ME!", rectGameOver.position.x + 20, rectGameOver.position.y + 103 );
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
    ofSetColor( colBlue );
    bgConfirmation.draw(0, 0);
    
    if (!isPlayerOneConfirmed) {
        ofSetColor( colBlue );
        ofRect( *geometries_->activeArea[0] );
        string      _text1   = "TOUCH PADDLE\n  TO START";
        ofPushMatrix();
        {
            ofSetColor( colBlue );
            ofRectangle bounds  = arcadeSmall.getStringBoundingBox(_text1, 0, 0);
            // Rotation point in the middle
            ofTranslate(bounds.width/2, bounds.height / 2, 0);
            // Flips X -> Y & Y -> -X
            ofRotateZ( 90 );
            arcadeSmall.drawString(_text1, geometries_->world.getHeight()/2 - (bounds.width/2) - 55,
                                          -geometries_->activeArea[0]->getWidth() /2 + (bounds.height/2) + 50 );
        }
        ofPopMatrix();
    }
    if (!isPlayerTwoConfirmed) {
        string      _text2   = "TOUCH PADDLE\n  TO START";
        ofSetColor( colGreen );
        ofRect( *geometries_->activeArea[1] );
        ofPushMatrix();
        {
            ofSetColor( colGreen );
            ofRectangle bounds  = arcadeSmall.getStringBoundingBox(_text2, 0, 0);
            ofTranslate(bounds.width/2, bounds.height / 2, 0);
            // Flips X -> -Y & Y -> X
            ofRotateZ( -90 );
            arcadeSmall.drawString(_text2, -geometries_->world.getHeight()/2 - (bounds.width/2) + 45,
                                          + geometries_->world.getHeight() - geometries_->activeArea[1]->getWidth() - (bounds.height ) - 275 );
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
    
	string roundWord;
	switch(roundOfGame_) {
		case 1: roundWord = " ONE"; break;
		case 2: roundWord = " TWO"; break;
		case 3: roundWord = "THREE"; break;
		case 4: roundWord = "FOUR"; break;
		case 5: roundWord = "FIVE"; break;
	}
    ofSetColor( colWhite );
	arcadeMedium.drawString( "ROUND\n" + roundWord, geometries_->world.getCenter().x - 180, geometries_->world.getCenter().y - 200);
	ofSetColor( colMagenta );
	arcadeLarge.drawString( ofToString(countDownPlaying.currentValue), geometries_->world.getCenter().x - 80, geometries_->world.getCenter().y + 300);
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
	
}
    
void IntermediateControl::resetGameOver()
{
    countDownGameOver.isSet = false;
}
    
void  IntermediateControl::drawPlanB()
{
    ofSetColor( ofColor::white );
    videoPlanB.draw(0, 0);
}
    
    
// ------------------------------------------------------------------------
    
}   // namespace telePong
