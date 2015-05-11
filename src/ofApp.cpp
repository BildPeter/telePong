#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);

    pongCalibrator.setPaddelSize( ofRectangle( 100, ofGetWindowHeight()/2, 50,200 ), ofRectangle( ofGetWindowWidth()-100, ofGetWindowHeight()/2, 50,200 ) );
    
    touchHandler.setup( 3333, "/tuio/2dcur");
    
    superPong.setBoundaries( pongCalibrator.getBoundaries() );
    superPong.init();
    
    ofEnableSmoothing();
    
//    tuioClient.start(3333);
    
    ofAddListener(tuioClient.cursorAdded,this,&ofApp::tuioAdded);
    ofAddListener(tuioClient.cursorRemoved,this,&ofApp::tuioRemoved);
    ofAddListener(tuioClient.cursorUpdated,this,&ofApp::tuioUpdated);


}

//--------------------------------------------------------------
void ofApp::update(){
    touchHandler.update();
    superPong.update();
//    tuioClient.getMessage();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( ofColor::black);
    touchHandler.drawVerbose();
    //    superPong.draw();
//    tuioClient.drawCursors();
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
    superPong.paddleLeft_->setPosition(100, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    superPong.paddleRight_->setPosition(ofGetWindowWidth()-100, y);
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


void ofApp::tuioAdded(ofxTuioCursor &tuioCursor){
    ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
    cout << "Point n" << tuioCursor.getSessionId() << " add at " << loc << endl;
}

void ofApp::tuioUpdated(ofxTuioCursor &tuioCursor){
    ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
    cout << "Point n" << tuioCursor.getSessionId() << " updated at " << loc << endl;
}

void ofApp::tuioRemoved(ofxTuioCursor &tuioCursor){
    ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
    cout << "Point n" << tuioCursor.getSessionId() << " remove at " << loc << endl;
}

