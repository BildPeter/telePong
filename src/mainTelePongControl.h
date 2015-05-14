#pragma once

#include "ofMain.h"
#include "ofxOscParameterSync.h"
#include "ofxGui.h"

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
		
    ofxOscParameterSync     syncParameters;
    
    ofParameterGroup    parameters;
    
    ofParameter<bool>   verboseCursorSwitch;
    ofParameter<bool>   verboseBlobsSwitch;
    ofParameter<bool>   autoGameSwitch;
    ofParameter<bool>   calibartaionSwitch;
    
    ofParameter<int>    sizeBall;
    ofParameter<int>    sizePaddleHight;
    ofParameter<int>    sizePaddleWidth;
    ofParameter<int>    calibartaionGridPoints;
    
    ofxPanel gui;

};
