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

void PongGame::updatePositions()
{
    // TODO Global width/height
    
    paddleLeft_->setPosition(   boundaries_->panels[0]->getX() + (boundaries_->panels[0]->width/2) ,
                                boundaries_->panels[0]->getY() + (boundaries_->panels[0]->height/2) );
    
    paddleRight_->setPosition(  boundaries_->panels[1]->getX()  + (boundaries_->panels[1]->width/2) ,
                                boundaries_->panels[1]->getY()  + (boundaries_->panels[1]->height/2) );

}
    
void PongGame::update()
{
    world_->update();
    updatePositions();
    
    restrictSpeed( ball_, 30 );
    catchBugVertical( ball_, 0.7 );
    resetBall( ball_ );
}

void PongGame::draw()
{
    ofNoFill();
    ofSetColor( 100, 100, 100);
    paddleLeft_->draw();
    paddleRight_->draw();
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
    world_->setFPS( ofGetFrameRate() );
    world_->registerGrabbing();
    cout << "world position; " <<ofGetWindowRect().getPosition() << "\n";
    world_->createBounds( worldRect_ );

    
    paddleLeft_->isFixed();
    paddleRight_->isFixed();
    paddleLeft_->setup(   world_->getWorld(), *boundaries_->panels[0] );
    paddleRight_->setup(  world_->getWorld(), *boundaries_->panels[1] );
    //    noStroke();
    
    ball_->setPhysics(3, 1, 0.1);
    ball_->setup( world_->getWorld(), ofGetWindowWidth()/2,ofGetWindowHeight()/2 , ballRadius_ );
}

void PongGame::restrictSpeed( shared_ptr< ofxBox2dCircle > mball_, int maxSpeed )
{
    if ( mball_->getVelocity().length() > maxSpeed)
        mball_->setVelocity( mball_->getVelocity().normalize()* maxSpeed );
}

void PongGame::catchBugVertical( shared_ptr< ofxBox2dCircle > mball, double tolerance )
{
    
    if ( ( ( mball->getVelocity().x <= tolerance ) && ( mball->getVelocity().x >= (-tolerance) ) ) && ( mball->getVelocity().y > 0.1 ) )
    {
        if ( mball->getVelocity().x >= 0 )
            mball->setVelocity( mball->getVelocity() + ofVec2f( ofRandom( tolerance*3, speedRestriction_ ), mball->getVelocity().y ) );
        else
            mball->setVelocity( mball->getVelocity() + ofVec2f( ofRandom( -tolerance*3, -speedRestriction_ ), mball->getVelocity().y ) );
    }
}

void PongGame::resetBall( shared_ptr< ofxBox2dCircle > mBall )
{
    int     distanceFromBorder = 5;
    
    if (     ( mBall->getPosition().x < worldRect_.getMinX() + (mBall->getRadius()*2) + distanceFromBorder )
        ||   ( mBall->getPosition().x > worldRect_.getMaxX() - (mBall->getRadius()*2) - distanceFromBorder ) )
    {
        mBall->setPosition( ofVec2f( worldRect_.getCenter().x, worldRect_.getCenter().y ) );
        mBall->setVelocity( ofVec2f::zero() );
        mBall->setRotation( 0 );
    }
}

void PongGame::rescaleBounds()
{
    world_->createBounds();
}
    
void PongGame::rescaleBounds( ofRectangle bounds )
{
    worldRect_ = bounds;
    world_->createBounds( worldRect_ );
}

PongGame::~PongGame()
{
    paddleLeft_.reset();
    paddleRight_.reset();
    ball_.reset();
    world_.reset();
}
    
}   // namespace telePong
