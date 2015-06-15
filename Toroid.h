//
//  Toroid.h
//  GLFW_Demo
//
//  Created by Ira on 6/11/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#ifndef __GLFW_Demo__Toroid__
#define __GLFW_Demo__Toroid__

#include <stdio.h>
#include "Geom.h"

class Toroid: public Geom {
    
public:
    Toroid();
    Toroid(float toroidRadius, float ringRadius, int toroidDetail, int ringDetail, const glm::vec4& col = glm::vec4(.76, .56, .456, 1.0));
    // must ocreated concrete implementations
    // of abstract functions (pure virtuals)
    void calcVerts();
    void calcInds();
    
    // properties
    float toroidRadius, ringRadius;
    int toroidDetail, ringDetail;
    
};


#endif /* defined(__GLFW_Demo__Toroid__) */










