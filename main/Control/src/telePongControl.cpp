#include "telePongControl.h"

//--------------------------------------------------------------
void ofApp::setup(){
    if( XML.loadFile("Settings.xml") ){
        cout << "Settings.xml loaded!\n";
    }else{
        cout << "unable to load Settings.xml check data/ folder\n";
    }
    string HOST = XML.getValue( "IP", "127.0.0.1" );
    
    parameters.setName("telePong");
    parameters.add( calibartaionSwitch.set( "Calibration ON/OFF", false ) );
    parameters.add( autoGameSwitch.set( "AutoGame ON/OFF", false ) );
    parameters.add( verboseSwitch.set( "Verbose", false ) );
    parameters.add( PlanBSwitch.set( "PlanB", false ) );
    
//    parameters.add(sizeBall.set( "Ball size",30,10,70) );
//    parameters.add(sizePaddleHight.set( "Paddle hight",30,10,70) );
//    parameters.add(sizePaddleWidth.set( "Paddle width",30,10,70) );
    parameters.add(calibartaionGridPoints.set( "Calibration grid points",4,1,5) );
 
    gui.setup(parameters);
    sender.setup( HOST, 4444 );
    cout << "IP: " << HOST << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

    {
        ofxOscMessage m;
        m.setAddress("/pong/calibration");
        m.addIntArg( calibartaionSwitch );
        sender.sendMessage(m);
    }
    {
        ofxOscMessage m;
        m.setAddress("/pong/autogame");
        m.addIntArg( autoGameSwitch );
        sender.sendMessage(m);
    }
    {
        ofxOscMessage m;
        m.setAddress("/pong/verbose");
        m.addIntArg( verboseSwitch );
        sender.sendMessage(m);
    }
    {
        ofxOscMessage m;
        m.setAddress("/pong/planb");
        m.addIntArg( PlanBSwitch );
        sender.sendMessage(m);
    }
    //    {
//        ofxOscMessage m;
//        m.setAddress("/pong/ballsize");
//        m.addIntArg( sizeBall );
//        sender.sendMessage(m);
//    }
//    {
//        ofxOscMessage m;
//        m.setAddress("/pong/paddleheight");
//        m.addIntArg( sizePaddleHight );
//        sender.sendMessage(m);
//    }
//    {
//        ofxOscMessage m;
//        m.setAddress("/pong/paddlewidth");
//        m.addIntArg( sizePaddleWidth );
//        sender.sendMessage(m);
//    }
    {
        ofxOscMessage m;
        m.setAddress("/pong/calibrationpoints");
        m.addIntArg( calibartaionGridPoints );
        sender.sendMessage(m);
    }
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
