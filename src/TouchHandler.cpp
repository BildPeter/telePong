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
    
//    cout << "POS x: " << tuioCursor.getX() << "\ty: " << tuioCursor.getY() << "\n";
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
    cout << "ADD x: " << tuioCursor.getX() << "\ty: " << tuioCursor.getY() << "\n";
    // ---  cursors will only be usefull, if they are inside the box from the start
    
    for ( auto & mTouch : touchVector_ )
    {
        if ( !mTouch.isSet() )
        {
            ofPoint     point   = ofPoint( (float)ofGetWidth() * tuioCursor.getX(), (float)ofGetHeight() * tuioCursor.getY() );
            for (int i = 0; i < boundaries_.paddels.size(); i++) {
                if ( boundaries_.paddels[i]->inside( point ) )
                {
                    mTouch.setEvent( tuioCursor, boundaries_.paddels[i]->getCenter(), i );
                    cout << "event set: " << mTouch.getSessionID() << "\n";
                }
            }
        }
    }
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
                cout << "event UNset: " << tuioCursor.getSessionId() << "\n";
            }
        }
    }
}

void TouchHandler::tuioUpdated(ofxTuioCursor &tuioCursor)
{
    for ( auto &mTouch : touchVector_ )
    {
        if ( mTouch.isSet() )
        {
            ofPoint     point   = ofPoint( (float)ofGetWidth() * tuioCursor.getX(), (float)ofGetWindowHeight() * tuioCursor.getY() );
            if ( boundaries_.paddels[ mTouch.getPaddleID() ]->inside( point ) )
            {
                boundaries_.paddels[ mTouch.getPaddleID() ]->setY( point.y - (boundaries_.paddels[ mTouch.getPaddleID() ]->height/2) + mTouch.getShiftY() );
                cout << "pos: " << point << "\n";
            } else
            {
                mTouch.unsetEvent();
            }
        }
    }
}
    
}   // namespace telePong
