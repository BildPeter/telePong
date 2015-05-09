//
//  TouchHandler.cpp
//  telePong
//
//  Created by Peter A. Kolski on 09.05.15.
//
//

#include "TouchHandler.h"

namespace telePong
{
    
void    TouchHandler::setupOSC( int port, string adress )
{
    oscPort_    = port;
    oscAdress_  = adress;    
    oscReciever_.setup( port );
}
    
}   // namespace telePong
