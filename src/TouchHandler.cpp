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
    touchVector_    = vector<TuioTouch>( boundaries_.panels.size() );
    
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
    ofNoFill();
    ofSetColor( ofColor::red );
    ofRect( *boundaries_.panels[0] );
    ofRect( *boundaries_.panels[1] );
}

bool    TouchHandler::isInBoundary( ofxTuioCursor &tuioCursor )
{
    // TODO transform coordinates
    ofPoint     point   = ofPoint( (float)ofGetWidth() * tuioCursor.getX(), (float)ofGetHeight() * tuioCursor.getY() );
    bool        isIn    = false;
    
    
    for ( auto &panel :  boundaries_.panels )
    {
        isIn = ( isIn || panel->
                inside( point ) );
    }
        
    return ( boundaries_.panels[0]->inside( point ) || boundaries_.panels[1]->inside( point )  );
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
            for (int i = 0; i < boundaries_.panels.size(); i++) {
                if ( boundaries_.panels[i]->inside( point ) )
                {
                    mTouch.setEvent( tuioCursor, boundaries_.panels[i]->getCenter(), i );
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
            if ( boundaries_.panels[ mTouch.getPaddleID() ]->inside( point ) )
            {
                boundaries_.panels[ mTouch.getPaddleID() ]->setY( point.y - (boundaries_.panels[ mTouch.getPaddleID() ]->height/2) + mTouch.getShiftY() );
                cout << "pos: " << point << "\n";
            } else
            {
                mTouch.unsetEvent();
            }
        }
    }
}
    
}   // namespace telePong
