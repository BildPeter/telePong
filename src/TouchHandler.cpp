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
    
void    TouchHandler::setupOSC( int port, string adress )
{
    oscPort_    = port;
    oscAdress_  = adress;    
    oscReciever_.setup( port );
}
    
void TouchHandler::update()
{
    while( oscReciever_.hasWaitingMessages() )
    {
        oscReciever_.getNextMessage( &oscMessage_ );
        int id;
        float   x, y;
        
        
        if (oscMessage_.getArgAsString(0) == "set")
        {
            if(oscMessage_.getArgType(1) == OFXOSC_TYPE_INT32){
                id = oscMessage_.getArgAsInt32(1);
            }

            if (oscMessage_.getArgType(2) == OFXOSC_TYPE_FLOAT)
            {
                x = oscMessage_.getArgAsFloat( 2 );
            }

            if (oscMessage_.getArgType(3) == OFXOSC_TYPE_FLOAT)
            {
                y = oscMessage_.getArgAsFloat( 3 );
            }
        
        cout << id << " " << x << " " << y << "\n";
        }
    }
}
}   // namespace telePong
