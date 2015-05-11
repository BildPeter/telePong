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
    
void    TouchHandler::setup( int port, string adress )
{
    oscPort_    = port;
    oscAdress_  = adress;    
    
    tuioClient.start( oscPort_ );
    
    ofAddListener(tuioClient.cursorAdded, this, &TouchHandler::tuioAdded );
    ofAddListener(tuioClient.cursorRemoved,this,&TouchHandler::tuioRemoved);
    ofAddListener(tuioClient.cursorUpdated,this,&TouchHandler::tuioUpdated);
}
    
void TouchHandler::update()
{
    tuioClient.getMessage();
}
    
void TouchHandler::drawVerbose()
{
    tuioClient.drawCursors();
}

void TouchHandler::tuioAdded(ofxTuioCursor &tuioCursor)
{
    cout << "added\n";
}
 
void TouchHandler::tuioRemoved(ofxTuioCursor &tuioCursor)
{
    cout << "removed\n";
}

void TouchHandler::tuioUpdated(ofxTuioCursor &tuioCursor)
{
    cout << "updated\n";
}
    
}   // namespace telePong
