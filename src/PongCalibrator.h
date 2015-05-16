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
    GeometryType            getGeometry() { return geometries_; }
    void                    setPaddelSize( ofRectangle &sizeLeft, ofRectangle &sizeRight );
    void                    setActiveArea( ofRectangle areaLeft, ofRectangle areaRight );
    
private:
    GeometryType            geometries_;
};
    
}   // namespace telePong

#endif /* defined(__telePong__PongCalibrator__) */
