#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
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
    mGeometry.world = ofRectangle( screenShift, 760 , 760 );
    
    screenControl.setup( portControl );
    touchHandler.setup( portTuio, mGeometry, globalGameState );
    controlIntermediate.setGameStateGlobal( globalGameState );
    controlIntermediate.setup( &touchHandler.getGeometry() );
    superPong.setup( &touchHandler.getGeometry(), globalGameState );
    
//    touchHandler.toggleTextVerbose();
    controlIntermediate.toggleTextVerbose();
    superPong.toggleTextVerbose();
// ----- TMP
}

//--------------------------------------------------------------
void ofApp::update(){
    
    touchHandler.setWorld( ofRectangle( screenShift, 760 , 760 ) );
    touchHandler.update();
    controlIntermediate.update( touchHandler.getCursorAll(), superPong.getRound(), superPong.getWinner() );
    superPong.update( touchHandler.getGeometry().world, touchHandler.getCursorActive() );
    
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
        ofRect(5, 5, touchHandler.getGeometry().world.getWidth() - 10, touchHandler.getGeometry().world.getHeight() - 10 );
        superPong.draw();
        controlIntermediate.draw();
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
        case 'a':
            globalGameState = telePong::AutoGame;
            break;
        case 'c':
            globalGameState = telePong::PlayerConfirmation;
            break;
        case 'p':
            globalGameState = telePong::Playing;
            break;
        case 'g':
            globalGameState = telePong::GameOver;
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
