#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofEnableSmoothing();
    
    int     portTuio    = 3333;
    int     portControl = 4444;
    screenScale  = 1;
    screenShift  = ofPoint(0, 0 );
    
//    pongCalibrator.setPaddelSize( ofRectangle( 100, ofGetWindowHeight()/2, 50,200 ), ofRectangle( ofGetWindowWidth()-100, ofGetWindowHeight()/2, 50,200 ) );
//    pongCalibrator.setPaddelSize( ofRectangle( 300, ofGetWindowHeight()/2, 300,300 ), ofRectangle( ofGetWindowWidth()-200, ofGetWindowHeight()/2, 300,300 ) );
//    pongCalibrator.setPaddelSize( mPadA, mPadA );
    
    mPadA.setFromCenter( 70, ofGetWindowHeight()/2, 50,100 );
    mPadB.setFromCenter( ofGetWindowWidth()-70, ofGetWindowHeight()/2, 50,100 );
    
    std::vector<ofRectangle>    mBund;
    std::vector<ofRectangle*>    mBundPntr;
    mBoundary.panels.push_back( &mPadA );
    mBoundary.panels.push_back( &mPadB );
    
    screenControl.setup( portControl );
    touchHandler.setup( portTuio, mBoundary );
    superPong.setBoundaries( &touchHandler.getBoundaries() );
    superPong.init();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    touchHandler.update();
    worldDimension = ofRectangle( screenShift, ofGetWindowHeight() * screenScale, ofGetWindowHeight() * screenScale );
    superPong.rescaleBounds(worldDimension);
    superPong.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0,0,0);

    ofSetColor(255, 255, 255 );
    ofNoFill();
    ofPushMatrix();
    {
        ofTranslate( screenShift );
        ofScale( screenScale, screenScale );
        ofRect(5, 5, ofGetWindowHeight() - 10, ofGetWindowHeight() - 10 );
        superPong.draw();
        touchHandler.drawVerbose();
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f')
    {
        ofToggleFullscreen();
        rescalePong();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
//    touchHandler.getBoundaries().panels[0].y = y;
//    superPong.paddleLeft_->setPosition( touchHandler.getBoundaries().panels[0].x, touchHandler.getBoundaries().panels[0].y );
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//    touchHandler.getBoundaries().panels[1].y = y;
//    superPong.paddleRight_->setPosition( touchHandler.getBoundaries().panels[1].x, touchHandler.getBoundaries().panels[1].y );
    
    if ( touchHandler.getBoundaries().panels[0]->inside( ofPoint(x,y) ) )
    {
        touchHandler.getBoundaries().panels[0]->setY( y );
        cout << "pos: " << ofPoint(x,y) << "\n";
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    rescalePong();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::rescalePong(){
    superPong.rescaleBounds();
    
    mPadA.setFromCenter( 70 , ofGetWindowHeight()/2, 50,100 );
    mPadB.setFromCenter( ofGetWindowHeight()-70, ofGetWindowHeight()/2, 50,100 );
    //        mBoundary.panels[ 0 ] = &mPadA;
    //        mBoundary.panels[ 1 ] = mPadB
    
    //        superPong.setBoundaries( );

}
