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
#include <set>


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
    void                setEvent( ofxTuioCursor &cursor, ofPoint boundaryCenter, int paddleID );
    
    void                unsetEvent()                        { eventCursor_ = 0;         cursorIsSet_ = false; }
    int                 getSessionID()                      { return eventCursor_->getSessionId(); }
    int                 getPaddleID()                       { return paddleID_; }
    float               getShiftY()                         { return shiftY_; }
    float               getX()                              { return eventCursor_->getX(); }
    float               getY()                              { return eventCursor_->getY(); }
    bool                isSet()                             { return cursorIsSet_; }
    
private:
    ofxTuioCursor  *eventCursor_;
    bool            cursorIsSet_;
    float           shiftY_;
    int             paddleID_;
};
    
    
class TouchHandler{
public:
    TouchHandler()
    {
        oscPort_        = 3333;
        verboseText     = false;
    }

    void                setup( int port, BoundaryType    boundary );
    void                setBoundray( BoundaryType    boundary )     { boundaries_     = boundary; }
    void                update();
    void                drawVerbose();
    void                drawPointStates();
    
    vector<TuioTouch>  &getTouches()                        { return touchVector_; }
    list<CursorPoint>  &getCursorPoints()                   { return cursorPoints_; }
    list<CursorPoint>   getActiveCursors();
    BoundaryType       &getBoundaries()                     { return boundaries_; }
    

    
private:
    void                    tuioAdded(      ofxTuioCursor & tuioCursor );
    void                    tuioRemoved(    ofxTuioCursor & tuioCursor );
    void                    tuioUpdated(    ofxTuioCursor & tuioCursor );
    bool                    isInBoundary(   ofxTuioCursor & tuioCursor );
    StateOfArea             getCursorPointState( ofPoint aPoint );
    Side                    getCursorPointSide( ofPoint aPoint );
    
    ofxTuioClient           tuioClient_;
    BoundaryType            boundaries_;
    int                     oscPort_;
    vector<TuioTouch>       touchVector_;
    vector<ofPoint>         positions_;
    bool                    verboseText;
    list<CursorPoint>       cursorPoints_;
    
};
    
}   // namespace telePong


#endif /* defined(__telePong__TouchHandler__) */
