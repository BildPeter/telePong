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

void PongGame::update()
{
    world_->update();
    
    restrictSpeed( ball_, 30 );
    catchBugVertical( ball_ );
    resetBall( ball_ );
}

void PongGame::draw()
{
    paddleLeft_->draw();
    paddleRight_->draw();
    ofSetColor( 200,200,200);
    ofFill();
    ball_->draw();
}

void PongGame::init()
{
    world_       = shared_ptr<ofxBox2d>( new ofxBox2d );
    ball_        = shared_ptr<ofxBox2dCircle>( new  ofxBox2dCircle );
    paddleLeft_  = shared_ptr< ofxBox2dRect >( new ofxBox2dRect );
    paddleRight_ = shared_ptr< ofxBox2dRect >( new ofxBox2dRect );
    
    world_->init();
    world_->setGravity(0, 0);
    world_->createBounds();
    world_->setFPS(60.0);
    world_->registerGrabbing();
    
    paddleLeft_->isFixed();
    paddleRight_->isFixed();
    paddleLeft_->setup(   world_->getWorld(), boundaries_.panels[0] );
    paddleRight_->setup(  world_->getWorld(), boundaries_.panels[1] );
    //    noStroke();
    
    ball_->setPhysics(3, 1, 0.1);
    ball_->setup( world_->getWorld(), ofGetWindowWidth()/2,ofGetWindowHeight()/2 , 30);
}

void PongGame::restrictSpeed( shared_ptr< ofxBox2dCircle > mball_, int maxSpeed )
{
    if ( mball_->getVelocity().length() > maxSpeed)
        mball_->setVelocity( mball_->getVelocity().normalize()* maxSpeed );
}

void PongGame::catchBugVertical( shared_ptr< ofxBox2dCircle > mball )
{
    if ( ( mball->getVelocity().x <= 1 ) && ( mball->getVelocity().y > 10 ) )
        mball->setVelocity( mball->getVelocity() + ofVec2f( ofRandom(-10, 10 ), ofRandom( -10, 10 ) ) );
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
    world_->createBounds();
}

PongGame::~PongGame()
{
    paddleLeft_.reset();
    paddleRight_.reset();
    ball_.reset();
    world_.reset();
}
    
}   // namespace telePong
