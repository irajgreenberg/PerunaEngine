//
//  Toroid.cpp
//  GLFW_Demo
//
//  Created by Ira on 6/11/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#include "Toroid.h"

Toroid::Toroid() {
    init();
}

Toroid::Toroid(float toroidRadius, float ringRadius, int toroidDetail, int ringDetail):
toroidRadius(toroidRadius), ringRadius(ringRadius), toroidDetail(toroidDetail), ringDetail(ringDetail)
{
    init();
}

// must include concrete implementations
// of abstract functions (pure virtuals)

// z-axis rotaiton
/*
 x' = x*cos q - y*sin q
 y' = x*sin q + y*cos q
 z' = z
 */

// Y-axis rotaiton
/*
 z' = z*cos q - x*sin q
 x' = z*sin q + x*cos q
 y' = y
 */


void Toroid::calcVerts() {
    glm::vec3 temp;
    float theta = 0.0;
    for(int i=0; i<toroidDetail; ++i){
        float phi = 0.0;
        // start with rot around y-axis
        temp.z = cos(theta)*toroidRadius;
        temp.x = sin(theta)*toroidRadius;
        temp.y = 0;
        for(int j=0; j<ringDetail; ++j){
            // now rotate around z-axis
            verts.push_back(glm::vec3( temp.x*cos(phi)*ringRadius - temp.y*sin(phi)*ringRadius, temp.x*sin(phi)*ringRadius + temp.y*cos(phi)*ringRadius, temp.z ));
            cols.push_back(glm::vec4(.75, .65, .85, 1.0));
            

            phi += M_PI*2/ringDetail;

            
            if (i<toroidDetail-1 && j<ringDetail-1){
                int a = i*ringDetail+j;
                int b = i*ringDetail+j+1;
                int c = (i+1)*ringDetail+j;
                int d = (i+1)*ringDetail+j+1;
                inds.push_back(Elem(a, d, b));
                inds.push_back(Elem(a, c, d));
            }
        }
        theta += M_PI*2/toroidDetail;
    }
}

void Toroid::calcInds() {
}

