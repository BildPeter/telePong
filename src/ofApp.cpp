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
    mRestrictA.set(0, 0, 200, ofGetWindowHeight() );
    mRestrictB.set(ofGetWindowWidth() - 200, 0, 200, ofGetWindowHeight() );
    
    mGeometry.paddels.push_back( &mPadA );
    mGeometry.paddels.push_back( &mPadB );
    mGeometry.activeArea.push_back( &mRestrictA );
    mGeometry.activeArea.push_back( &mRestrictB );
    
    screenControl.setup( portControl );
    touchHandler.setup( portTuio, mGeometry );
    superPong.setBoundaries( &touchHandler.getBoundaries() );
    superPong.init();
    
// ----- TMP
}

//--------------------------------------------------------------
void ofApp::update(){
    
    touchHandler.update();
    worldDimension = ofRectangle( screenShift, (float)ofGetWindowHeight() , (float)ofGetWindowHeight() );
    superPong.rescaleBounds(worldDimension);
    superPong.setActivePoints( touchHandler.getActiveCursors() );
    superPong.update();
    
// ----- TMP

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
    // ----- TMP
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
//    superPong.setAttraction( x  , y );
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
