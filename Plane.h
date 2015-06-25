//
//  Plane.h
//  GLFW_Demo
//
//  Created by Ira on 6/25/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#ifndef __GLFW_Demo__Plane__
#define __GLFW_Demo__Plane__

#include <stdio.h>
#include "Geom.h"

class Plane: public Geom {
    
public:
    Plane();
    Plane(const glm::vec4& col, const std::string& diffuseMap);
    // must ocreated concrete implementations
    // of abstract functions (pure virtuals)
    void calcVerts();
    void calcInds();
};


#endif /* defined(__GLFW_Demo__Plane__) */
