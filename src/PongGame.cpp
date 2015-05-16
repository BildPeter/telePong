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

void PongGame::setup( GeometryType *geometry, GameState &state )
{
    geometries_  = geometry;
    stateOfGame_ = &state;
    
    world_       = shared_ptr< ofxBox2d >( new ofxBox2d );
    ball_        = shared_ptr< ofxBox2dRect>( new  ofxBox2dRect );
    paddleLeft_  = shared_ptr< ofxBox2dRect >( new ofxBox2dRect );
    paddleRight_ = shared_ptr< ofxBox2dRect >( new ofxBox2dRect );
    
    maxRoundsGame       = 2;
    isPlaying           = false;
    tweenDuration       = 4000;
    tweenDelay          = 0;
    tweenlinear.setParameters(0,easinglinear,ofxTween::easeOut,4,1,tweenDuration,tweenDelay);
    tweenlinear.start();
    ofTrueTypeFont::setGlobalDpi(72);
    fontVerdana.loadFont("verdana.ttf", 30, true, true);
    fontVerdana.setLineHeight(34.0f);
    fontVerdana.setLetterSpacing(1.035);
    
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
}

void PongGame::update( ofRectangle bounds, list<CursorPoint> activeCursors  )
{
    activeCursors_ = activeCursors;
    rescaleBounds( bounds );
    
    if ( *stateOfGame_ == Playing ) {
        world_->update();
        updatePositions();
        restrictSpeed( ball_, 30, 5 );
        catchBugVertical( ball_, 0.7 );
        resetBall( ball_ );
        updateStartingGame();
    }
}
    
void PongGame::updateStartingGame()
{
    if( !isPlaying )
    {
        if ( !tweenlinear.isCompleted() ) {
            tweenCountDown = tweenlinear.update();
            cout << tweenCountDown << "\n";
        }else
        {
            startBall();
            isPlaying = true;
        }
    }
}
    

void PongGame::draw()
{
    ofFill();
    ofSetColor( 255, 255, 255);
    paddleLeft_->draw();
    paddleRight_->draw();
    ball_->draw();
    if ( (!isPlaying)&&( *stateOfGame_ == Playing ) ) {
        ofSetColor( ofColor::white );
        fontVerdana.drawString( "Round "+ofToString(roundOfGame)+"\n"+ofToString(tweenCountDown),
                               geometries_->world.getCenter().x, geometries_->world.getCenter().y +50);
    }
}
    
// ----------------------------------------------------------------------

void PongGame::updatePositions()
{
    bool isLeftSet  = false;
    bool isRightSet = false;
    // TODO Global width/height
    for( auto actPoint : activeCursors_ )
    {
        if( actPoint.side == left ){
            if ( actPoint.state == Paddle ) {
                paddleLeft_->setPosition( geometries_->paddels[0]->getX() + geometries_->paddels[0]->width/2,
                                          geometries_->paddels[0]->getY() + geometries_->paddels[0]->height/2 - actPoint.shiftY);
            }else{
                setAttractionLeft( actPoint.position.y, 20 );
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
                setAttractionRight( actPoint.position.y, 20 );
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
    if (roundOfGame == maxRoundsGame) {
        roundOfGame     = 0;
        *stateOfGame_   = GameOver;
        if (verboseText_) { cout <<"GameState: GameOver\n"; }
    }else
    {
        roundOfGame++;
    }
}

void PongGame::resetBall( shared_ptr< ofxBox2dRect > mBall )
{
    int     distanceFromBorder = 0;
    
    if (     ( mBall->getPosition().x < (*geometries_).world.getMinX() + (mBall->getWidth()) + distanceFromBorder )
        ||   ( mBall->getPosition().x > (*geometries_).world.getMaxX() - (mBall->getWidth()) - distanceFromBorder ) )
    {
        mBall->setPosition( ofVec2f( (*geometries_).world.getCenter().x, (*geometries_).world.getCenter().y ) );
        mBall->setVelocity( ofVec2f::zero() );
        mBall->setRotation( 0 );
        mBall->setAngularVelocity( 0 );

        nextRound();
        isPlaying = false;
        tweenlinear.setParameters(0,easinglinear,ofxTween::easeOut,4,1,tweenDuration,tweenDelay);
        tweenlinear.start();
        if (verboseText_) {cout<<"Round: " << roundOfGame +1<<"\n";};
    }
}

    
void PongGame::startBall()
{
    float  signX = ( ofRandom(-1, 1) > 0 ) ? 1 : (-1);
    float  signY = ( ofRandom(-1, 1) > 0 ) ? 1 : (-1);
    ball_->setVelocity( signX * ofRandom( speedRestriction_/4.0, speedRestriction_/2 ) , signY * ofRandom( 0, speedRestriction_ ) );
}



void PongGame::restrictSpeed( shared_ptr< ofxBox2dRect > mball_, int maxSpeed, int maxRotSpeed )
{
    if ( mball_->getVelocity().length() > maxSpeed)
        mball_->setVelocity( mball_->getVelocity().normalize()* maxSpeed );

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
        if ( mball->getVelocity().x >= 0 )
            mball->setVelocity( mball->getVelocity() + ofVec2f( ofRandom( tolerance*3, speedRestriction_ ), mball->getVelocity().y ) );
        else
            mball->setVelocity( mball->getVelocity() + ofVec2f( ofRandom( -tolerance*3, -speedRestriction_ ), mball->getVelocity().y ) );
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
