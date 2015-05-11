#pragma once

#include "ofMain.h"
#include "ofxTuio.h"

#include "PongGame.h"
#include "PongHelpers.h"
#include "PongCalibrator.h"
#include "TouchHandler.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    telePong::PongGame          superPong;
    telePong::Calibrator        pongCalibrator;
    telePong::BoundaryType      boundaries;
    telePong::TouchHandler      touchHandler;
    
    void	tuioAdded(ofxTuioCursor & tuioCursor);
    void	tuioRemoved(ofxTuioCursor & tuioCursor);
    void	tuioUpdated(ofxTuioCursor & tuioCursor);
    
    ofxTuioClient   tuioClient;

};

