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
        
    mPadA.setFromCenter( 70, ofGetWindowHeight()/2, 50,100 );
    mPadB.setFromCenter( ofGetWindowWidth()-70, ofGetWindowHeight()/2, 50,100 );
    
    mBoundary.paddels.push_back( &mPadA );
    mBoundary.paddels.push_back( &mPadB );
    
    screenControl.setup( portControl );
    touchHandler.setup( portTuio, mBoundary );
    superPong.setBoundaries( &touchHandler.getBoundaries() );
    superPong.init();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    touchHandler.update();
    worldDimension = ofRectangle( screenShift, (float)ofGetWindowHeight() , (float)ofGetWindowHeight() );
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
    }
    ofPopMatrix();

    touchHandler.drawVerbose();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case 'f':
            ofToggleFullscreen();
            rescalePong();
        case 's':
            superPong.startBall();
            break;
        case '+':
            screenScale += 0.01;
            break;
        case '-':
            screenScale -= 0.01;
            break;
        case OF_KEY_LEFT:
            screenShift.x -= 2;
            break;
        case OF_KEY_RIGHT:
            screenShift.x += 2;
            break;
        case OF_KEY_UP:
            screenShift.y -= 2;
            break;
        case OF_KEY_DOWN:
            screenShift.y += 2;
            break;
            
        default:
            break;
    }

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
}
