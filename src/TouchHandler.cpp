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
//    oscReciever_.setup( port );
    
    tuioClient.start( oscPort_ );
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
        cout << "Test works\n";
    }
    
}   // namespace telePong
