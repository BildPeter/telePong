#include "telePongControl.h"

//--------------------------------------------------------------
void ofApp::setup(){
    parameters.setName("telePong");
    parameters.add( calibartaionSwitch.set( "Calibration ON/OFF", false ) );
    parameters.add( autoGameSwitch.set( "AutoGame ON/OFF", false ) );
    parameters.add( verboseBlobsSwitch.set( "Show Blobs", false ) );
    parameters.add( verboseCursorSwitch.set( "Show Cursor", false ) );
    
    parameters.add(sizeBall.set( "Ball size",30,10,70) );
    parameters.add(sizePaddleHight.set( "Paddle hight",30,10,70) );
    parameters.add(sizePaddleWidth.set( "Paddle width",30,10,70) );
    parameters.add(calibartaionGridPoints.set( "Calibration grid points",1,1,5) );
 
    gui.setup(parameters);
    syncParameters.setup((ofParameterGroup&)gui.getParameter(),3333,"172.20.10.2",3333);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
