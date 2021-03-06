#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    globalGameState = telePong::Calibartion;
    
    if( XML.loadFile("Settings.xml") ){
        cout << "Settings.xml loaded!\n";
    }else{
        cout << "unable to load Settings.xml check data/ folder\n";
    }
    int sizeBall        = XML.getValue( "BALLSIZE", 30 );
    int paddleWidth     = XML.getValue( "PADDLEWIDTH", 50 );
    int paddleHeight    = XML.getValue( "PADDLEHEIGHT", 100 );
    int speedMin        = XML.getValue("SPEEDMIN", 10);
    int speedMax        = XML.getValue("SPEEDMAX", 12);
    
    int     portTuio    = 3333;
    int     portControl = 4444;
    screenScale  = 1;
    screenShift  = ofPoint(0, 0 );
    
    mPadA.setFromCenter( 70, ofGetWindowHeight()/2, paddleWidth, paddleHeight );
    mPadB.setFromCenter( ofGetWindowWidth()-70, ofGetWindowHeight()/2, paddleWidth, paddleHeight );
    mRestrictA.set(0, 0, 200, ofGetWindowHeight() );
    mRestrictB.set(ofGetWindowWidth() - 200, 0, 200, ofGetWindowHeight() );
    
    mGeometry.paddels.push_back( &mPadA );
    mGeometry.paddels.push_back( &mPadB );
    mGeometry.activeArea.push_back( &mRestrictA );
    mGeometry.activeArea.push_back( &mRestrictB );
    mGeometry.world = ofRectangle( screenShift, 760 , 760 );
    
    screenControlOSC.setup( portControl );
    touchHandler.setup( portTuio, mGeometry, globalGameState );
    controlIntermediate.setGameStateGlobal( globalGameState );
    controlIntermediate.setup( &touchHandler.getGeometry() );
    superPong.setup( &touchHandler.getGeometry(), globalGameState, sizeBall );
    superPong.setBallSpeedRestriction( speedMin, speedMax );
    
    #ifdef _WIN32
		ofxSpout::init("telePong", ofGetWidth(), ofGetHeight(), true);
    #endif
    
    touchHandler.toggleVerbose( false );
    controlIntermediate.toggleVerbose( false );
    superPong.toggleVerbose( false );
    verbose = false;
// ----- TMP
}

//--------------------------------------------------------------
void ofApp::update(){
    
    updateOSC();
    touchHandler.setWorld( ofRectangle( screenShift, 760 , 760 ) );
    touchHandler.update( superPong.getBallPosition() );
    controlIntermediate.update( touchHandler.getCursorAll(), superPong.getRound(), superPong.getWinner(), superPong.getPointOfPlayer() );
    superPong.update( touchHandler.getGeometry().world, touchHandler.getCursorActive() );
    
// ----- TMP

}

//--------------------------------------------------------------
void ofApp::draw(){

	#ifdef _WIN32
		ofxSpout::initSender();
	#endif

    ofClear(0,0,0);

    ofSetColor(255, 255, 255 );
    ofNoFill();
    ofPushMatrix();
    {
        ofTranslate( screenShift );
        ofScale( screenScale, screenScale );
        //ofRect(5, 5, touchHandler.getGeometry().world.getWidth() - 10, touchHandler.getGeometry().world.getHeight() - 10 );
        controlIntermediate.draw();
        superPong.draw();
    }
    ofPopMatrix();

    touchHandler.draw();
    // ----- TMP

	#ifdef _WIN32
		ofxSpout::sendTexture();
	#endif
}


//--------------------------------------------------------------

void ofApp::keyPressed(int key){

    switch (key) {
        case 's':
            superPong.startBall();
            break;
        case 'a':
            globalGameState = telePong::AutoGame;
            break;
        case 'c':
            globalGameState = telePong::Calibartion;
            break;
        case 'p':
            globalGameState = telePong::Playing;
            break;
        case 'g':
            globalGameState = telePong::GameOver;
            break;
        case 'b':
            globalGameState = telePong::PlanB;
            break;
        case 'v':
            verbose = verbose==true?false:true;
            controlIntermediate.toggleVerbose(verbose);
            touchHandler.toggleVerbose(verbose);
            break;
        case '+':
            controlIntermediate.increaseRasterPointsIdle();
            break;
        case '-':
            controlIntermediate.decreaseRasterPointsIdle();
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

void ofApp::updateOSC()
{
while(screenControlOSC.hasWaitingMessages()){
    ofxOscMessage m;
    screenControlOSC.getNextMessage(&m);
    
    if(m.getAddress() == "/pong/calibration")
    {
        if (m.getArgAsInt32(0))
        {
            globalGameState = telePong::Calibartion;
        }
    } else if ( m.getAddress() == "/pong/autogame" )
    {
        if (m.getArgAsInt32(0))
        {
            globalGameState = telePong::AutoGame;
        }
    } else if ( m.getAddress() == "/pong/verbose" )
    {
        if (m.getArgAsInt32(0))
        {
            superPong.toggleVerbose( true );
            touchHandler.toggleVerbose( true );
            controlIntermediate.toggleVerbose( true );
        }else
        {
            superPong.toggleVerbose( false );
            touchHandler.toggleVerbose( false );
            controlIntermediate.toggleVerbose( false );
        }
        
    } else if ( m.getAddress() == "/pong/planb" )
    {
        if (m.getArgAsInt32(0))
        {
            globalGameState = telePong::PlanB;
        }
    } else if ( m.getAddress() == "/pong/ballsize" )
    {
    } else if ( m.getAddress() == "/pong/paddleheight" )
    {
    } else if ( m.getAddress() == "/pong/paddlewidth" )
    {
    } else if ( m.getAddress() == "/pong/calibrationpoints" )
    {
        controlIntermediate.setRasterPoints( m.getArgAsInt32(0) );
    }
    
}
}