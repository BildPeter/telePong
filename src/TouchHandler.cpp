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
    drawPointStates();
}

void TouchHandler::drawPointStates(){
    ofFill();
    for ( auto aPoint : getActiveCursors() ){
        ofSetColor( ofColor::blue );
        ofCircle( aPoint.position, 15 );
    }
    
    for ( auto &aPoint : cursorPoints_ )
    {
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
    
    CursorPoint           aPoint;
    aPoint.sessionID    = tuioCursor.getSessionId();
    aPoint.state        = getCursorPointState( tPoint );
    aPoint.side         = getCursorPointSide( tPoint );
    aPoint.position     = tPoint;
    cursorPoints_.push_back(aPoint);
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
    
    for ( auto i = cursorPoints_.begin(); i!= cursorPoints_.end(); ++i)
    {
        if (i->sessionID == tuioCursor.getSessionId() ) {
            cursorPoints_.erase(i);
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
    
    for ( CursorPoint &point  : cursorPoints_)
    {
        if ( point.sessionID == tuioCursor.getSessionId() )
        {
            point.position  = tPoint;
            point.state     = getCursorPointState( tPoint );
            point.side      = getCursorPointSide( tPoint );
        }
    }
}
    
StateOfArea TouchHandler::getCursorPointState( ofPoint aPoint )
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
    
Side   TouchHandler::getCursorPointSide( ofPoint aPoint )
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
    
list<CursorPoint>  TouchHandler::getActiveCursors()
{
    CursorPoint             mLeft;
    CursorPoint             mRight;
    mLeft.position          = ofPoint(0,0);
    mRight.position         = ofPoint(0,0);
    float distanceLeft      = 400000;
    float distanceRight     = 400000;
    list< CursorPoint >     result;
    
    
    for ( auto &mCursor : cursorPoints_){
        if (mCursor.side == left )
        {
            if (mCursor.state == Paddle ) {
                mLeft = mCursor;
            }else if ( mCursor.state == ActiveArea ){
                float currentDistance = mCursor.position.distance(  boundaries_.paddels[0]->position );
                if ( currentDistance < distanceLeft ) {
                    distanceLeft = currentDistance;
                    mLeft = mCursor;
                }
            }
        }
        if (mCursor.side == right )
        {
            if (mCursor.state == Paddle ) {
                mRight = mCursor;
            }else if ( mCursor.state == ActiveArea ){
                float currentDistance = mCursor.position.distance(  boundaries_.paddels[1]->position );
                if ( currentDistance < distanceRight ) {
                    distanceRight = currentDistance;
                    mRight = mCursor;
                }
            }
        }
    }
    if ( mLeft.position != ofPoint(0,0) ) {
        result.push_back( mLeft );
    }
    if ( mRight.position != ofPoint(0,0) ) {
        result.push_back( mRight );
    }
    
    return result;
}
    
}   // namespace telePong
