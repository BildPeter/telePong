//
//  PongGame.cpp
//  PongBox
//
//  Created by Peter A. Kolski on 03.05.15.
//
//

#include "PongGame.h"

void PongGame::update()
{
    world->update();
    
    restrictSpeed( ball, 30 );
    catchBugVertical( ball );
    resetBall( ball );
}

void PongGame::draw()
{
    paddleLeft->draw();
    paddleRight->draw();
    ofSetColor( 200,200,200);
    ofFill();
    ball->draw();
}

void PongGame::init()
{
    world       = shared_ptr<ofxBox2d>( new ofxBox2d );
    ball        = shared_ptr<ofxBox2dCircle>( new  ofxBox2dCircle );
    paddleLeft  = shared_ptr< ofxBox2dRect >( new ofxBox2dRect );
    paddleRight = shared_ptr< ofxBox2dRect >( new ofxBox2dRect );
    
    world->init();
    world->setGravity(0, 0);
    world->createBounds();
    world->setFPS(60.0);
    world->registerGrabbing();
    
    paddleLeft->isFixed();
    paddleRight->isFixed();
    paddleLeft->setup(   world->getWorld(), 100, ofGetWindowHeight()/2, 50,200);
    paddleRight->setup(  world->getWorld(), ofGetWindowWidth()-100, ofGetWindowHeight()/2, 50,200);
    //    noStroke();
    
    ball->setPhysics(3, 1, 0.1);
    ball->setup( world->getWorld(), ofGetWindowWidth()/2,ofGetWindowHeight()/2 , 30);
}

void PongGame::restrictSpeed( shared_ptr< ofxBox2dCircle > mBall, int maxSpeed )
{
    if ( mBall->getVelocity().length() > maxSpeed)
        mBall->setVelocity( mBall->getVelocity().normalize()* maxSpeed );
}

void PongGame::catchBugVertical( shared_ptr< ofxBox2dCircle > mBall )
{
    if ( ( mBall->getVelocity().x <= 1 ) && ( mBall->getVelocity().y > 10 ) )
        mBall->setVelocity( mBall->getVelocity() + ofVec2f( ofRandom(-10, 10 ), ofRandom( -10, 10 ) ) );
}

void PongGame::resetBall( shared_ptr< ofxBox2dCircle > mBall )
{
    int     distanceFromBorder = 5;
    if (     ( mBall->getPosition().x < mBall->getRadius() + distanceFromBorder )
        ||   ( mBall->getPosition().x > ofGetWindowWidth() - mBall->getRadius() - distanceFromBorder ) )
    {
        mBall->setPosition( ofVec2f( ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 ) );
        mBall->setVelocity( ofVec2f::zero() );
        mBall->setRotation( 0 );
    }
}

void PongGame::rescaleBounds()
{
    world->createBounds();
}

PongGame::~PongGame()
{
    paddleLeft.reset();
    paddleRight.reset();
    ball.reset();
    world.reset();
}
