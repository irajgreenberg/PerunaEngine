//
//  Face.h
//  GLFW_Demo
//
//  Created by Ira on 6/3/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#ifndef __GLFW_Demo__Face__
#define __GLFW_Demo__Face__

#include <stdio.h>
#include "glm/glm.hpp"

struct Face {
    
    glm::vec3 v0, v1, v2;
    
    Face(){
    }
    
    Face(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2):
    v0(v0), v1(v1), v2(v2)
    {
    }
    
};

#endif /* defined(__GLFW_Demo__Face__) */
