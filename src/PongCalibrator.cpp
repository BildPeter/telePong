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
    boundaries_.panelLeft.panelSize     = sizeLeft;
    boundaries_.panelRight.panelSize    = sizeRight;
}

void Calibrator::setActiveArea( ofRectangle areaLeft, ofRectangle areaRight )
{
    boundaries_.panelLeft.activeArea    = areaLeft;
    boundaries_.panelRight.activeArea   = areaRight;
}
    
}   // namespace telePong
