#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofEnableSmoothing();
    
//    pongCalibrator.setPaddelSize( ofRectangle( 100, ofGetWindowHeight()/2, 50,200 ), ofRectangle( ofGetWindowWidth()-100, ofGetWindowHeight()/2, 50,200 ) );
    pongCalibrator.setPaddelSize( ofRectangle( 300, ofGetWindowHeight()/2, 300,300 ), ofRectangle( ofGetWindowWidth()-200, ofGetWindowHeight()/2, 300,300 ) );

    touchHandler.setup(3333, pongCalibrator.getBoundaries() );
    superPong.setBoundaries( &touchHandler.getBoundaries() );
    superPong.init();
}

//--------------------------------------------------------------
void ofApp::update(){
    touchHandler.update();
    superPong.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( ofColor::black);
    superPong.draw();
    touchHandler.drawVerbose();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f')
    {
        ofToggleFullscreen();
        superPong.rescaleBounds();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    touchHandler.getBoundaries().panels[0].y = y;
    superPong.paddleLeft_->setPosition( touchHandler.getBoundaries().panels[0].x, touchHandler.getBoundaries().panels[0].y );
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    touchHandler.getBoundaries().panels[1].y = y;
//    superPong.paddleRight_->setPosition( touchHandler.getBoundaries().panels[1].x, touchHandler.getBoundaries().panels[1].y );
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