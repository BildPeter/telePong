//
//  PongHelpers.h
//  telePong
//
//  Created by Peter A. Kolski on 09.05.15.
//
//

#ifndef telePong_PongHelpers_h
#define telePong_PongHelpers_h

#include "ofMain.h"
#include <set>

namespace telePong
{
    using namespace std;

struct GeometryType
{
    std::vector<ofRectangle*>   activeArea;
    std::vector<ofRectangle*>   paddels;
    ofRectangle                 world;
};
    
enum StateOfArea
{
    Paddle,
    ActiveArea,
    InvalidArea
};

enum Side
{
    left,
    right,
    middle
};

struct CursorPoint
{
    int             sessionID;
    ofPoint         position;
    StateOfArea     state;
    Side            side;
    float           shiftY;
};
    
enum GameState{ Idle, AutoGame, PlayerConfirmation, RoundCountDown, Playing, GameOver };
enum WinnerType{ None, Left, Right };
    
struct CountDown
{
    int max;
    int currentValue;
    int initialValue;
    int isSet;
};

    
}   // namespace telePong

#endif
