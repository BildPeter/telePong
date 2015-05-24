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
    
class TouchHandler{
public:
    TouchHandler()
    {
        oscPort_        = 3333;
        verboseText_    = false;
    }

    void                setup( int port, GeometryType    geometry, GameState &state );
    void                update();
    void                drawVerbose();
    void                drawPointStates();
    
    void                setWorld( ofRectangle world )      { geometries_.world = world; }
    
    list<CursorPoint>  &getCursorAll()                      { return cursorPoints_; }
    list<CursorPoint>   getCursorActive()                   { return activeCursors_; }
    GeometryType       &getGeometry()                       { return geometries_; }
    void                toggleTextVerbose()                 { verboseText_ = verboseText_?false:true;}
    
private:
    void                    tuioAdded(      ofxTuioCursor & tuioCursor );
    void                    tuioRemoved(    ofxTuioCursor & tuioCursor );
    void                    tuioUpdated(    ofxTuioCursor & tuioCursor );
    bool                    isInGeometry(   ofxTuioCursor & tuioCursor );
    StateOfArea             getCursorPointState( ofPoint aPoint );
    Side                    getCursorPointSide( ofPoint aPoint );
    float                   getShift( ofxTuioCursor & tuioCursor, CursorPoint const &aPoint );
    void                    calculateClosestActiveCursors();
    
    ofxTuioClient           tuioClient_;
    GeometryType            geometries_;
    int                     oscPort_;
    vector<ofPoint>         positions_;
    bool                    verboseText_;
    list<CursorPoint>       cursorPoints_;
    list<CursorPoint>       activeCursors_;
    GameState              *stateOfGame_;
};
    
}   // namespace telePong


#endif /* defined(__telePong__TouchHandler__) */
