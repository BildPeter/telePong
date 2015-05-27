//
//  PongGame.cpp
//  telePong
//
//  Created by Peter A. Kolski on 03.05.15.
//
//

#include "PongGame.h"

namespace telePong
{

void PongGame::setup( GeometryType *geometry, GameState &state, int ballSize )
{
    geometries_  = geometry;
    stateOfGame_ = &state;
    ballRadius_  = ballSize;
    
    world_       = shared_ptr< ofxBox2d >( new ofxBox2d );
    ball_        = shared_ptr< ofxBox2dRect>( new  ofxBox2dRect );
    paddleLeft_  = shared_ptr< ofxBox2dRect >( new ofxBox2dRect );
    paddleRight_ = shared_ptr< ofxBox2dRect >( new ofxBox2dRect );
    startBall_   = false;
    
    maxRoundsGame       = 5;
    
    world_->init();
    world_->setGravity(0, 0);
    world_->setFPS( ofGetFrameRate() );
    world_->registerGrabbing();
    cout << "world position; " <<ofGetWindowRect().getPosition() << "\n";
    world_->createBounds( geometries_->world );
    
    paddleRight_->setPhysics(3, 0, 100);
    paddleLeft_->setPhysics(3, 0, 100);
    paddleLeft_->setup(   world_->getWorld(), *geometries_->paddels[0] );
    paddleRight_->setup(  world_->getWorld(), *geometries_->paddels[1] );
    
    ball_->setPhysics(0.1, 1, 0.1);
    ball_->setup( world_->getWorld(), ofGetWindowWidth()/2,ofGetWindowHeight()/2 , ballRadius_, ballRadius_ );
    updatePositions();
    setCursorActiveCentered();
    resetGame();
}
    
void PongGame::setCursorActiveCentered()
{
    CursorPoint             mLeft;
    CursorPoint             mRight;
    
    mLeft.position      = ofPoint( geometries_->paddels[0]->position.x, ofGetWindowHeight()/2 );
    mRight.position     = ofPoint( geometries_->paddels[1]->position.x, ofGetWindowHeight()/2 );
    mLeft.side          = left;
    mRight.side         = right;
    mLeft.state         = ActiveArea;
    mRight.state        = ActiveArea;
    
    activeCursorsCentered_.push_back(mLeft);
    activeCursorsCentered_.push_back(mRight);
}


void PongGame::update( ofRectangle bounds, list<CursorPoint> activeCursors  )
{
    rescaleBounds( bounds );
    
    if (*stateOfGame_ == RoundCountDown) {
        updateRoundCountDown();
        startBall_ = true;
    }
    
    if ( *stateOfGame_ == Playing ) {
        activeCursors_ = activeCursors;
        if (startBall_) {
            startBall();
            startBall_ = false;
        }
        updateGameMovement();
    }
    if ( *stateOfGame_ == AutoGame ) {
//        if (startBall_) {
//            startBall();
//            startBall_ = false;
//        }
        updateAutoGame();
    }
    
    if (*stateOfGame_ == GameOver ) {
        updateRoundCountDown();
        startBall_ = true;
    }
}
    
void PongGame::updateGameMovement()
{
    updatePositions();
    world_->update();
    restrictSpeed( ball_, 5 );
    catchBugVertical( ball_, 0.7 );
    resetBallAtBoundary( ball_ );
}
    
void PongGame::updateRoundCountDown()
{
    activeCursors_ = activeCursorsCentered_;
    updatePositions();
    world_->update();
}

void PongGame::updateAutoGame()
{
    world_->update();
    restrictSpeed( ball_, 5 );
    catchBugVertical( ball_, 0.7 );
    resetBallAtBoundary( ball_ );
}

void PongGame::draw()
{
    ofFill();
    ofSetColor( ofColor::fromHex( ofHexToInt( "64b9e4" ) ) );
    paddleLeft_->draw();
    ofSetColor( ofColor::fromHex( ofHexToInt( "babd5a" ) ) );
    paddleRight_->draw();
    
    if (    ( *stateOfGame_ == Playing )
        ||  ( *stateOfGame_ == RoundCountDown )
        )
    {
        ofSetColor( ofColor::fromHex( ofHexToInt( "e20074" ) ) );
        ball_->draw();
    }
}
    
// ----------------------------------------------------------------------

void PongGame::updatePositions()
{
    bool isLeftSet  = false;
    bool isRightSet = false;

    for( CursorPoint const &actPoint : activeCursors_ )
    {
        if( actPoint.side == left ){
            if ( actPoint.state == Paddle ) {
                paddleLeft_->setPosition( geometries_->paddels[0]->getX() + geometries_->paddels[0]->width/2,
                                          geometries_->paddels[0]->getY() + geometries_->paddels[0]->height/2);
            }else{
                setAttractionLeft( actPoint.position.y, 40 );
                paddleLeft_->setDamping(0.95);
                paddleLeft_->setRotation(0);
                paddleLeft_->setVelocity(0, paddleLeft_->getVelocity().y );
                geometries_->paddels[0]->setPosition( geometries_->paddels[0]->getX(),
                                                      paddleLeft_->getPosition().y - (geometries_->paddels[0]->height/2) );
            }
            isLeftSet = true;
        }
        if( actPoint.side == right ){
            if ( actPoint.state == Paddle ) {
                paddleRight_->setPosition( geometries_->paddels[1]->getX() + (geometries_->paddels[1]->width/2) ,
                                           geometries_->paddels[1]->getY() + (geometries_->paddels[1]->height/2) );
            }else{
                setAttractionRight( actPoint.position.y, 40 );
                paddleRight_->setDamping(0.95);
                paddleRight_->setRotation(0);
                paddleRight_->setVelocity(0, paddleRight_->getVelocity().y );
                geometries_->paddels[1]->setPosition( geometries_->paddels[1]->getX(),
                                                     paddleRight_->getPosition().y - (geometries_->paddels[1]->height/2) );            }
            isRightSet = true;
        }
    }

    // -- If the cursor leaves or disappears. Stop the movement
    if (!isLeftSet) {
        paddleLeft_->setPosition( geometries_->paddels[0]->getX() + (geometries_->paddels[0]->width/2) ,
                                  geometries_->paddels[0]->getY() + (geometries_->paddels[0]->height/2) );
    }
    if (!isRightSet) {
        paddleRight_->setPosition( geometries_->paddels[1]->getX() + (geometries_->paddels[1]->width/2) ,
                                   geometries_->paddels[1]->getY() + (geometries_->paddels[1]->height/2) );
    }
}
    
// ----------------------------------------------------------------------
    
void PongGame::nextRound()
{
    if (roundOfGame_ < maxRoundsGame) {
        resetRound();
        if (verboseText_) { cout <<"GameState: RoundCountDown\n"; }
    }else
    {
        if (pointsRight>pointsLeft) { winnerFinal = Right; }
        else                        { winnerFinal = Left; }
        resetGame();
        *stateOfGame_   = GameOver;
        if (verboseText_) { cout <<"GameState: GameOver\n"; }
    }
}

void PongGame::resetBallAtBoundary( shared_ptr< ofxBox2dRect > mBall )
{
    int     distanceFromBorder = 0;
    
    if (     ( mBall->getPosition().x < (*geometries_).world.getMinX() + (mBall->getWidth()) + distanceFromBorder )
        ||   ( mBall->getPosition().x > (*geometries_).world.getMaxX() - (mBall->getWidth()) - distanceFromBorder ) )
    {
        if (mBall->getPosition().x < (*geometries_).world.getCenter().x) {
            pointsRight++;
            winnerLast = Right;
            if (verboseText_) { cout << "point for right\t" <<pointsLeft<<":"<<pointsRight<<"\n"; }
        }else{
            pointsLeft++;
            winnerLast = Left;
            if (verboseText_) { cout << "point for left\t" <<pointsLeft<<":"<<pointsRight<<"\n"; }
        }
        
        mBall->setPosition( ofVec2f( (*geometries_).world.getCenter().x, (*geometries_).world.getCenter().y ) );
        mBall->setVelocity( ofVec2f::zero() );
        mBall->setRotation( 0 );
        mBall->setAngularVelocity( 0 );

        
        nextRound();
        if (verboseText_) {cout<<"Round: " << roundOfGame_ +1<<"\n";};
    }
}

    
void PongGame::startBall()
{
    float  signY = ( ofRandom(-1, 1) > 0 ) ? 1 : (-1);
    float  signX;
    if (winnerLast == Right) {
        signX = -1;
    }else if (winnerLast == Left ){
        signX = 1;
    }else{
        signX = ( ofRandom(-1, 1) > 0 ) ? 1 : (-1);
    }
    ball_->setVelocity( signX * ofRandom( speedBallMin_, speedBallMax_/3 ) ,
                        signY * ofRandom( 0, speedBallMax_ ) );
}

void PongGame::resetGame()
{
    roundOfGame_        = 1;
    speedFactorPerRound = 1;
    setBallSpeed( 5, 10 );
    pointsLeft          = 0;
    pointsRight         = 0;
    winnerLast          = None;
}
    
void PongGame::resetRound()
{
    roundOfGame_++;
    speedFactorPerRound = roundOfGame_ + 1;
    setBallSpeed( 5 + speedFactorPerRound, 10 + 2*speedFactorPerRound);
    *stateOfGame_   = RoundCountDown;

//    geometries_->paddels[0]->setY( geometries_->activeArea[0]->getCenter().y - (geometries_->paddels[0]->height/2) );
//    geometries_->paddels[1]->setY( geometries_->activeArea[1]->getCenter().y - (geometries_->paddels[1]->height/2));
}


void PongGame::restrictSpeed( shared_ptr< ofxBox2dRect > mball_, int maxRotSpeed )
{
    if ( mball_->getVelocity().length() > speedBallMax_)
        mball_->setVelocity( mball_->getVelocity().normalize()* speedBallMax_ );
    if ( mball_->getVelocity().length() < speedBallMin_)
        mball_->setVelocity( mball_->getVelocity().normalize()* speedBallMin_ );
    
    if (mball_->getAngularVelocity() >= maxRotSpeed )
    {
        mball_->setAngularVelocity( maxRotSpeed );
    }
    if (mball_->getAngularVelocity() <= -maxRotSpeed )
    {
        mball_->setAngularVelocity( -maxRotSpeed );
    }
    
}

void PongGame::catchBugVertical( shared_ptr< ofxBox2dRect > mball, double tolerance )
{
    
    if ( ( ( mball->getVelocity().x <= tolerance ) && ( mball->getVelocity().x >= (-tolerance) ) ) && ( mball->getVelocity().y > 0.01 ) )
    {
        mball->setRotation( 45 );
        if ( mball->getVelocity().x >= 0 )
            mball->setVelocity( mball->getVelocity() + ofVec2f( ofRandom( tolerance*3, speedBallMax_ ), mball->getVelocity().y ) );
        else
            mball->setVelocity( mball->getVelocity() + ofVec2f( ofRandom( -tolerance*3, -speedBallMax_ ), mball->getVelocity().y ) );
    }
}

    
void PongGame::setAttractionRight( int y, float amount )
{
    paddleRight_->addAttractionPoint(geometries_->paddels[1]->getX()+ geometries_->paddels[1]->width/2, y, amount);
}

void PongGame::setAttractionLeft( int y, float amount )
{
    paddleLeft_->addAttractionPoint(geometries_->paddels[0]->getX() + geometries_->paddels[0]->width/2, y, amount);
}
    

    
void PongGame::rescaleBounds()
{
    world_->createBounds();
    updatePositions();
}
    
void PongGame::rescaleBounds( ofRectangle bounds )
{
    (*geometries_).world = bounds;
    world_->createBounds( (*geometries_).world );
    updatePositions();
}

PongGame::~PongGame()
{
    paddleLeft_.reset();
    paddleRight_.reset();
    ball_.reset();
    world_.reset();
}

    
}   // namespace telePong
