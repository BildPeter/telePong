//
//  TouchHandler.cpp
//  telePong
//
//  Created by Peter A. Kolski on 09.05.15.
//
//

#include "TouchHandler.h"

using namespace std;

namespace telePong
{
    
void   TuioTouch::setEvent( ofxTuioCursor &cursor, ofPoint boundaryCenter, int paddleID )
{
    eventCursor_    = &cursor;
    cursorIsSet_    = true;
    paddleID_       = paddleID;
    shiftY_         = -( ofGetWindowHeight() * eventCursor_->getY() ) + boundaryCenter.y;
}
    
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
    
void    TouchHandler::setup( int port, BoundaryType    boundary )
{
    boundaries_     = boundary;
    oscPort_        = port;
    touchVector_    = vector<TuioTouch>( boundaries_.paddels.size() );
    
    tuioClient_.start( oscPort_ );
    
    ofAddListener(tuioClient_.cursorAdded, this, &TouchHandler::tuioAdded );
    ofAddListener(tuioClient_.cursorRemoved,this,&TouchHandler::tuioRemoved);
    ofAddListener(tuioClient_.cursorUpdated,this,&TouchHandler::tuioUpdated);
}

void TouchHandler::update()
{
    tuioClient_.getMessage();
}
    
void TouchHandler::drawVerbose()
{
    tuioClient_.drawCursors();
    tuioClient_.drawObjects();
    ofNoFill();
    ofSetColor( ofColor::red );
    ofRect( *boundaries_.paddels[0] );
    ofRect( *boundaries_.paddels[1] );
}

void TouchHandler::drawPointStates(){
    for ( auto &aPoint : activePoints_ )
    {
        ofFill();
        switch (aPoint.state) {
            case InvalidArea:
                ofSetColor( ofColor::red );
                break;
                
            case ActiveArea:
                ofSetColor( ofColor::green );
                break;
                
            case Paddle:
                ofSetColor( ofColor::yellow );
                break;
                
            default:
                break;
        }
        ofCircle( aPoint.position, 10 );
    }
}
    
bool    TouchHandler::isInBoundary( ofxTuioCursor &tuioCursor )
{
    // TODO transform coordinates
    ofPoint     point   = ofPoint( (float)ofGetWidth() * tuioCursor.getX(), (float)ofGetHeight() * tuioCursor.getY() );
    bool        isIn    = false;
    
    
    for ( auto &paddel :  boundaries_.paddels )
    {
        isIn = ( isIn || paddel->
                inside( point ) );
    }
        
    return ( boundaries_.paddels[0]->inside( point ) || boundaries_.paddels[1]->inside( point )  );
}
    
void TouchHandler::tuioAdded(ofxTuioCursor &tuioCursor)
{
    if ( verboseText ) {   cout << "ADD x: " << tuioCursor.getX() << "\ty: " << tuioCursor.getY() << "\n"; }
    // ---  cursors will only be usefull, if they are inside the box from the start
    ofPoint     tPoint   = ofPoint( (float)ofGetWidth() * tuioCursor.getX(), (float)ofGetHeight() * tuioCursor.getY() );
    
    for ( auto & mTouch : touchVector_ )
    {
        if ( !mTouch.isSet() )
        {
            for (int i = 0; i < boundaries_.paddels.size(); i++) {
                if ( boundaries_.paddels[i]->inside( tPoint ) )
                {
                    mTouch.setEvent( tuioCursor, boundaries_.paddels[i]->getCenter(), i );
                    if ( verboseText ) { cout << "event set: " << mTouch.getSessionID() << "\n"; }
                }
            }
        }
    }
    
    ActivePoint           aPoint;
    aPoint.sessionID    = tuioCursor.getSessionId();
    aPoint.state        = getActivePointState( tPoint );
    aPoint.side         = getActivePointSide( tPoint );
    aPoint.position     = tPoint;
    activePoints_.push_back(aPoint);
}
 
void TouchHandler::tuioRemoved(ofxTuioCursor &tuioCursor)
{
    for ( auto & mTouch : touchVector_ )
    {
        if ( mTouch.isSet() )
        {
            if (mTouch.getSessionID() == tuioCursor.getSessionId() )
            {
                mTouch.unsetEvent();
                if ( verboseText ) {   cout << "event UNset: " << tuioCursor.getSessionId() << "\n"; }
            }
        }
    }
    
    for ( auto i = activePoints_.begin(); i!= activePoints_.end(); ++i)
    {
        if (i->sessionID == tuioCursor.getSessionId() ) {
            activePoints_.erase(i);
        }
    }
}

void TouchHandler::tuioUpdated(ofxTuioCursor &tuioCursor)
{
    ofPoint     tPoint   = ofPoint( (float)ofGetWidth() * tuioCursor.getX(), (float)ofGetWindowHeight() * tuioCursor.getY() );

    for ( auto &mTouch : touchVector_ )
    {
        if ( mTouch.isSet() )
        {
            if ( boundaries_.paddels[ mTouch.getPaddleID() ]->inside( tPoint ) )
            {
                boundaries_.paddels[ mTouch.getPaddleID() ]->setY( tPoint.y - (boundaries_.paddels[ mTouch.getPaddleID() ]->height/2) + mTouch.getShiftY() );
                if ( verboseText ) { cout << "pos: " << tPoint << "\n"; }
            } else
            {
                mTouch.unsetEvent();
            }
        }
    }
    
    for ( ActivePoint &point  : activePoints_)
    {
        if ( point.sessionID == tuioCursor.getSessionId() )
        {
            point.position  = tPoint;
            point.state     = getActivePointState( tPoint );
            point.side      = getActivePointSide( tPoint );
        }
    }
}
    
StateOfArea TouchHandler::getActivePointState( ofPoint aPoint )
{
    StateOfArea state    = InvalidArea;
    for ( ofRectangle *actArea : boundaries_.activeArea )
    {
        if ( actArea->inside( aPoint ) )  { state = ActiveArea; }
    }
    for ( ofRectangle *paddleArea : boundaries_.paddels )
    {
        if ( paddleArea->inside( aPoint ) )  { state = Paddle; }
    }
    return state;
}
    
Side   TouchHandler::getActivePointSide( ofPoint aPoint )
{
    Side mSide;
    if ( boundaries_.activeArea[0]->inside( aPoint ) )
    {
        mSide = left;
    }else if (boundaries_.activeArea[1]->inside( aPoint ) )
    {
        mSide = right;
    }else
    {
        mSide = middle;
    }
    
    return mSide;
}
    
    
}   // namespace telePong
