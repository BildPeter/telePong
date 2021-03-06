//
//  TouchHandler.cpp
//  telePong
//
//  Created by Peter A. Kolski on 09.05.15.
//
//

#include "TouchHandler.h"

using namespace std;

namespace telePong
{
    
void    TouchHandler::setup( int port, GeometryType    geometry, GameState &state )
{
    geometries_         = geometry;
    oscPort_            = port;
    stateOfGame_        = &state;
    
    tuioClient_.start( oscPort_ );
    
    ofAddListener(tuioClient_.cursorAdded, this, &TouchHandler::tuioAdded );
    ofAddListener(tuioClient_.cursorRemoved,this,&TouchHandler::tuioRemoved);
    ofAddListener(tuioClient_.cursorUpdated,this,&TouchHandler::tuioUpdated);
}

// ---------------------------------------------------------------------------
    
void TouchHandler::update( ofPoint ballPosition )
{
    if ( *stateOfGame_ == AutoGame ) {
        updateAutogame( ballPosition );
    }

    tuioClient_.getMessage();
}
    
void TouchHandler::updateAutogame( ofPoint ballPosition )
{
//    ofPoint     tPoint   = ofPoint( (float)ofGetWidth() * ballPosition.x, (float)ofGetHeight() * ballPosition.y );
//    
//    CursorPoint             aPoint;
//    aPoint.sessionID        = -1;
//    aPoint.state            = getCursorPointState( tPoint );
//    aPoint.side             = getCursorPointSide( tPoint );
//    aPoint.position         = tPoint;
//    aPoint.shiftY           = 0;
//    aPoint.timeLastMovement = ofGetElapsedTimef();
//    cursorPoints_.push_back(aPoint);
//    
//    calculateClosestActiveCursors();
}
    
// ---------------------------------------------------------------------------
    
void TouchHandler::draw()
{
    if (*stateOfGame_ !=PlanB) {
        if ( verboseText_ ) {
            drawVerbose();
            drawPointStates();
        }
    }
}
    
    
void TouchHandler::drawVerbose()
{
    tuioClient_.drawCursors();
    tuioClient_.drawObjects();
    ofNoFill();
    ofSetColor( ofColor::red );
    ofRect( *geometries_.paddels[0] );
    ofRect( *geometries_.paddels[1] );
    drawPointStates();
}
    
// ---------------------------------------------------------------------------
    
void TouchHandler::drawPointStates(){
    ofFill();
    for ( CursorPoint const &aPoint : getCursorActive() ){
        ofSetColor( ofColor::blue );
        ofCircle( aPoint.position, 15 );
    }
    
    for ( CursorPoint const &aPoint : cursorPoints_ )
    {
        switch (aPoint.state) {
            case InvalidArea:
                ofSetColor( ofColor::red );
                break;
                
            case ActiveArea:
                ofSetColor( ofColor::yellow );
                break;
                
            case Paddle:
                ofSetColor( ofColor::green );
                break;
                
            default:
                break;
        }
        ofCircle( aPoint.position, 10 );
    }
}
    
// ---------------------------------------------------------------------------
    
bool    TouchHandler::isInGeometry( ofxTuioCursor &tuioCursor )
{
    // TODO transform coordinates
    ofPoint     point   = ofPoint( (float)ofGetWidth() * tuioCursor.getX(), (float)ofGetHeight() * tuioCursor.getY() );
    bool        isIn    = false;
    
    
    for ( ofRectangle* paddel :  geometries_.paddels )
    {
        isIn = ( isIn || paddel->
                inside( point ) );
    }
        
    return ( geometries_.paddels[0]->inside( point ) || geometries_.paddels[1]->inside( point )  );
}
    
// ---------------------------------------------------------------------------
    
void TouchHandler::tuioAdded(ofxTuioCursor &tuioCursor)
{
    if ( verboseText_ ) {   cout << "ADD x: " << tuioCursor.getX() << "\ty: " << tuioCursor.getY() << "\n"; }
 
    ofPoint     tPoint   = ofPoint( (float)ofGetWidth() * tuioCursor.getX(), (float)ofGetHeight() * tuioCursor.getY() );
    
    CursorPoint           aPoint;
    aPoint.sessionID        = tuioCursor.getSessionId();
    aPoint.state            = getCursorPointState( tPoint );
    aPoint.side             = getCursorPointSide( tPoint );
    aPoint.position         = tPoint;
//    aPoint.shiftY           = getShift( tuioCursor, aPoint);
    aPoint.timeLastMovement = ofGetElapsedTimef();
    cursorPoints_.push_back(aPoint);
    
    calculateClosestActiveCursors();
}
 
// ---------------------------------------------------------------------------
    
void TouchHandler::tuioRemoved(ofxTuioCursor &tuioCursor)
{

	auto i = cursorPoints_.begin();
	while(i!=cursorPoints_.end()){
		if ( i->sessionID == tuioCursor.getSessionId() ) {
			cursorPoints_.erase(i++);
		} else {
			++i;
		}
	}
    
    calculateClosestActiveCursors();
}

// ---------------------------------------------------------------------------
    
void TouchHandler::tuioUpdated(ofxTuioCursor &tuioCursor)
{
    ofPoint     tPoint   = ofPoint( (float)ofGetWidth() * tuioCursor.getX(), (float)ofGetWindowHeight() * tuioCursor.getY() );
    
    // --- Update the cursors and theirs states
    for ( CursorPoint &point  : cursorPoints_)
    {
        if ( point.sessionID == tuioCursor.getSessionId() )
        {
            point.position          = tPoint;
            point.state             = getCursorPointState( tPoint );
            point.side              = getCursorPointSide( tPoint );
            point.timeLastMovement  = ofGetElapsedTimef();
        }
    }
    calculateClosestActiveCursors();

    // TODO Hier werden die Werte überschrieben, falls viele aktive Cursoren existieren
    if ( *stateOfGame_ == Playing ) {
        for ( CursorPoint &cursor : activeCursors_ )
        {
            if ( ( cursor.side == left ) && ( cursor.state == Paddle ) ) {
                geometries_.paddels[ 0 ]->setY( cursor.position.y - (geometries_.paddels[ 0 ]->height/2) );
            }
            if ( ( cursor.side == right ) && ( cursor.state == Paddle ) ) {
                geometries_.paddels[ 1 ]->setY( cursor.position.y - (geometries_.paddels[ 1 ]->height/2) );
            }
        }
    }
}
    
    
// ---------------------------------------------------------------------------
    
StateOfArea TouchHandler::getCursorPointState( ofPoint aPoint )
{
    StateOfArea state    = InvalidArea;
    for ( ofRectangle *actArea : geometries_.activeArea )
    {
        if ( actArea->inside( aPoint ) )
            { state = ActiveArea; }
    }
    if      (  (   (geometries_.paddels[0]->getRight()  > aPoint.x )
                && (geometries_.paddels[0]->getTop()    < aPoint.y )
                && (geometries_.paddels[0]->getBottom() > aPoint.y ) )
        ||     (   (geometries_.paddels[1]->getLeft()   < aPoint.x )
                && (geometries_.paddels[1]->getTop()    < aPoint.y )
                && (geometries_.paddels[1]->getBottom() > aPoint.y ) ) )
    {
        state = Paddle;
    }
    
    return state;
}

// ---------------------------------------------------------------------------
    
Side   TouchHandler::getCursorPointSide( ofPoint aPoint )
{
    Side mSide;
    if ( geometries_.activeArea[0]->inside( aPoint ) )
    {
        mSide = left;
    }else if (geometries_.activeArea[1]->inside( aPoint ) )
    {
        mSide = right;
    }else
    {
        mSide = middle;
    }
    
    return mSide;
}
    
// ---------------------------------------------------------------------------
    
void    TouchHandler::calculateClosestActiveCursors()
{
    CursorPoint             mLeft;
    CursorPoint             mRight;
    mLeft.position          = ofPoint(-1,-1);
    mRight.position         = ofPoint(-1,-1);
    mLeft.state             = InvalidArea;
    mRight.state            = InvalidArea;
    float distanceLeft      = 400000;
    float distanceRight     = 400000;
    activeCursors_.clear();             // TODO Sollen sie immer gelöscht werden?
    bool                    isLeftSet   = false;
    bool                    isRightSet  = false;
    
    for ( CursorPoint &mCursor : cursorPoints_)
    {
        // --- Check if active cursor is not set to a paddle yet
        if ( (mCursor.side == left ) && ( mLeft.state != Paddle ) && ( ( mCursor.timeLastMovement - ofGetElapsedTimef() ) < 5 ) )
        {
            if (mCursor.state == Paddle ) {
                mLeft = mCursor;
                isLeftSet = true;
            }else if ( mCursor.state == ActiveArea){
                float currentDistance = mCursor.position.distance(  geometries_.paddels[0]->position );
                if ( currentDistance < distanceLeft ) {
                    distanceLeft = currentDistance;
                    mLeft = mCursor;
                    isLeftSet = true;
                }
            }
        }
        if ( (mCursor.side == right ) && ( mRight.state != Paddle ) && ( ( mCursor.timeLastMovement - ofGetElapsedTimef() ) < 5 ) )
        {
            if (mCursor.state == Paddle ) {
                mRight = mCursor;
                isRightSet = true;
            }else if ( mCursor.state == ActiveArea ){
                float currentDistance = mCursor.position.distance(  geometries_.paddels[1]->position );
                if ( currentDistance < distanceRight ) {
                    distanceRight = currentDistance;
                    mRight = mCursor;
                    isRightSet = true;
                }
            }
        }
    }
    
    if ( isLeftSet ) {
        activeCursors_.push_back( mLeft );
    }
    if ( isRightSet ) {
        activeCursors_.push_back( mRight );
    }
}
    
// ---------------------------------------------------------------------------
    
float TouchHandler::getShift( ofxTuioCursor & tuioCursor, CursorPoint const &aPoint )
{
    float _shift;
    if ( (aPoint.state == Paddle)&&(aPoint.side == left ) ) {
        _shift  = -( ofGetWindowHeight() * tuioCursor.getY() ) + geometries_.paddels[0]->y;
    }else
    if ( (aPoint.state == Paddle)&&(aPoint.side == right ) ) {
        _shift  = -( ofGetWindowHeight() * tuioCursor.getY() ) + geometries_.paddels[1]->y;
    }else
        _shift = 0;

    return _shift;
}
    
}   // namespace telePong
