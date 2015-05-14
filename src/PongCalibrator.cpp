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
    
void Calibrator::setPaddelSize( ofRectangle &sizeLeft, ofRectangle &sizeRight)
{
//        boundaries_.panels.push_back( sizeLeft );
//        boundaries_.panels.push_back( sizeRight );
}

void Calibrator::setActiveArea( ofRectangle areaLeft, ofRectangle areaRight )
{
    boundaries_.activeArea.push_back( &areaLeft );
    boundaries_.activeArea.push_back( &areaRight );
}
    
}   // namespace telePong
