//
//  PongCalibrator.h
//  telePong
//
//  Created by Peter A. Kolski on 09.05.15.
//
//

#ifndef __telePong__PongCalibrator__
#define __telePong__PongCalibrator__

#include <iostream>
#include "PongHelpers.h"

namespace telePong
{

class   Calibrator{
public:
    GeometryType            getBoundaries() { return boundaries_; }
    void                    setPaddelSize( ofRectangle &sizeLeft, ofRectangle &sizeRight );
    void                    setActiveArea( ofRectangle areaLeft, ofRectangle areaRight );
    
private:
    GeometryType            boundaries_;
};
    
}   // namespace telePong

#endif /* defined(__telePong__PongCalibrator__) */
