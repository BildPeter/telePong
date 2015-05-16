#pragma once

#include "ofMain.h"
#include "ofxTuio.h"
#ifdef _WIN32
	#include "ofxSpout.h"
#endif

#include "PongGame.h"
#include "PongHelpers.h"
#include "PongCalibrator.h"
#include "PongIntermediate.h"
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
    void rescalePong();
    
    telePong::PongGame              superPong;
    telePong::IntermediateControl   controlIntermediate;
    telePong::Calibrator            pongCalibrator;
    telePong::TouchHandler          touchHandler;
    telePong::GeometryType          mGeometry;
    telePong::GameState             globalGameState;
    
    ofxOscReceiver                  screenControl;
    ofRectangle                     worldDimension;
    
    float                           screenScale;
    ofPoint                         screenShift;
    
    // --- TMP
    ofRectangle                     mPadA, mPadB, mRestrictA, mRestrictB;
};

