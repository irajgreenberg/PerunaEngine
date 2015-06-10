//
//  Elem.h
//  GLFW_Demo
//
//  Created by Ira on 6/3/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#ifndef GLFW_Demo_Elem_h
#define GLFW_Demo_Elem_h

struct Elem {
    
    int e0, e1, e2;
    
    Elem(): e0(0), e1(1), e2(2) {
    }
    
    Elem(int e0, int e1, int e2): e0(e0), e1(e1), e2(e2) {
    }
};

#endif
