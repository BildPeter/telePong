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
            if ( boundaries_.panels[0]->inside( point ) )
            {
                mTouch.setEvent( tuioCursor );
                cout << "event set: " << mTouch.getID() << "\n";
            }
            if ( boundaries_.panels[1]->inside( point ) )
            {
                mTouch.setEvent( tuioCursor );
                cout << "event set: " << mTouch.getID() << "\n";
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
            if (mTouch.getID() == tuioCursor.getSessionId() )
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
            if ( boundaries_.panels[0]->inside( point ) )
            {
                boundaries_.panels[0]->setY( point.y - (boundaries_.panels[0]->height/2)  );
                cout << "pos: " << point << "\n";
            }
            if ( boundaries_.panels[1]->inside( point ) )
            {
                boundaries_.panels[1]->setY( point.y - (boundaries_.panels[1]->height/2) );
                cout << "pos: " << point << "\n";
            }
        }
    }
}
    
}   // namespace telePong
