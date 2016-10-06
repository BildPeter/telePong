#pragma once

#include "ofMain.h"
#include "ofxOscSender.h"
#include "ofxXmlSettings.h"
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
		
    ofxOscSender        sender;
    ofxXmlSettings      XML;
    ofParameterGroup    parameters;
    
    ofParameter<bool>   verboseSwitch;
    ofParameter<bool>   autoGameSwitch;
    ofParameter<bool>   calibartaionSwitch;
    ofParameter<bool>   PlanBSwitch;
    
//    ofParameter<int>    sizeBall;
//    ofParameter<int>    sizePaddleHight;
//    ofParameter<int>    sizePaddleWidth;
    ofParameter<int>    calibartaionGridPoints;
    
    ofxPanel gui;

};
