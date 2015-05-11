//
//  PongCalibrator.cpp
//  telePong
//
//  Created by Peter A. Kolski on 09.05.15.
//
//

#include "PongCalibrator.h"



namespace telePong
{
    
void Calibrator::setPaddelSize( ofRectangle sizeLeft, ofRectangle sizeRight)
{
        boundaries_.panels[0]    = sizeLeft;
        boundaries_.panels[1]    = sizeRight;
}

void Calibrator::setActiveArea( ofRectangle areaLeft, ofRectangle areaRight )
{
    boundaries_.activeArea[0]    = areaLeft;
    boundaries_.activeArea[1]    = areaRight;
}
    
}   // namespace telePong
