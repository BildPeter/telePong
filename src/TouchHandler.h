//
//  TouchHandler.h
//  telePong
//
//  Created by Peter A. Kolski on 09.05.15.
//
//

#ifndef __telePong__TouchHandler__
#define __telePong__TouchHandler__

#include <iostream>
#include "PongHelpers.h"
#include "ofxOsc.h"
#include "ofxTuio.h"


namespace telePong
{

//class ITouch
//{
//public:
//    virtual float   getX()      = 0;
//    virtual float   getY()      = 0;
//    virtual int     getID()     = 0;
//    virtual bool    isSet()     = 0;
//};
    
    
class TuioTouch
{
public:
    void            setEvent( ofxTuioCursor &cursor )   { eventCursor_ = &cursor;   cursorIsSet_ = true; }
    void            unsetEvent()                        { eventCursor_ = 0;         cursorIsSet_ = false; }
    
    float           getX()                              { return eventCursor_->getX(); }
    float           getY()                              { return eventCursor_->getY(); }
    int             getID()                             { return eventCursor_->getSessionId(); }
    bool            isSet()                             { return cursorIsSet_; }
    
private:
    ofxTuioCursor  *eventCursor_;
    bool            cursorIsSet_;
};
    
    
class TouchHandler{
public:
    void                update();
    void                setBoundaries( BoundaryType boundary )  { boundaries_ = boundary; }
    void                setup( int port );
    void                drawVerbose();

private:
    void	tuioAdded(      ofxTuioCursor & tuioCursor );
    void	tuioRemoved(    ofxTuioCursor & tuioCursor );
    void	tuioUpdated(    ofxTuioCursor & tuioCursor );
    
    bool    isInBoundary(   ofxTuioCursor & tuioCursor );
    
    ofxTuioClient       tuioClient;

    
    BoundaryType        boundaries_;
    string              oscAdress_  = "";
    int                 oscPort_    = 3333;
    
};
    
}   // namespace telePong


#endif /* defined(__telePong__TouchHandler__) */
