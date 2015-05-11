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
    
void    TouchHandler::setup( int port, BoundaryType<2> &boundary )
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
}
    
void TouchHandler::drawVerbose()
{
    tuioClient_.drawCursors();
}

bool    TouchHandler::isInBoundary( ofxTuioCursor &tuioCursor )
{
    // TODO transform coordinates
    ofPoint     point   = ofPoint( ofGetWidth() * tuioCursor.getX(), ofGetHeight() * tuioCursor.getY() );
    bool        isIn    = false;
    
    for ( auto &panel :  boundaries_.panels )
    {
        isIn = ( isIn || panel.inside( point ) );
    }
        
    return isIn;
}
    
void TouchHandler::tuioAdded(ofxTuioCursor &tuioCursor)
{
    for ( auto & mTouch : touchVector_ )
    {
        if ( !mTouch.isSet() )
        {
            if ( isInBoundary( tuioCursor ) ) {
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
    for ( auto & mTouch : touchVector_ )
    {
        if ( mTouch.isSet() )
        {
            if (mTouch.getID() == tuioCursor.getSessionId() )
            {
                ofPoint     mPoint   = ofPoint( ofGetWidth() * tuioCursor.getX(), ofGetHeight() * tuioCursor.getY() );

                if ( boundaries_.panels[0].inside( mPoint ) ) {
                    boundaries_.panels[0].setY( mPoint.y );
                    cout << "New Coordinate: " << boundaries_.panels[0].getPosition() << "\n";
                }
                if ( boundaries_.panels[1].inside( mPoint ) ) {
                    boundaries_.panels[1].setY( mPoint.y );
                    cout << "New Coordinate: " << boundaries_.panels[1].getPosition() << " \n";
                }
            }
        }
    }

}
    
}   // namespace telePong
