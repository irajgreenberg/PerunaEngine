//
//  Cube.h
//  GLFW_Demo
//
//  Created by Ira on 6/3/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#ifndef __GLFW_Demo__Cube__
#define __GLFW_Demo__Cube__

#include <stdio.h>
#include "Geom.h"

class Cube: public Geom {
    
public:
    Cube();
    // must ocreated concrete implementations
    // of abstract functions (pure virtuals)
    void calcVerts();
    void calcInds();
};

#endif /* defined(__GLFW_Demo__Cube__) */
