//
//  Plane.cpp
//  GLFW_Demo
//
//  Created by Ira on 6/3/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#include "Plane.h"

Plane::Plane() {
    for (int i = 0; i < 4; ++i){
        this->cols.push_back(glm::vec4(1, 1, 1, 1.0));
    }
    //createDiffuseMapTexture( --add string-- );
    init();
}

Plane::Plane(const glm::vec4& col, const std::string& diffuseMap){
    for (int i = 0; i < 4; ++i){
        this->cols.push_back(col);
    }
    createDiffuseMapTexture(diffuseMap);
    init();
}

// must include concrete implementations
// of abstract functions (pure virtuals)
void Plane::calcVerts() {
    verts.push_back(glm::vec3(-.5, 0, .5));
    verts.push_back(glm::vec3(.5, 0, .5));
    verts.push_back(glm::vec3(.5, 0, -.5));
    verts.push_back(glm::vec3(-.5, 0, -.5));
    
    glm::vec2 scaleFactor(5, 5);
    uvs.push_back(glm::vec2(0, 0));
    uvs.push_back(glm::vec2(1*scaleFactor.x, 0));
    uvs.push_back(glm::vec2(1*scaleFactor.x, 1*scaleFactor.y));
    uvs.push_back(glm::vec2(0, 1*scaleFactor.y));

}

void Plane::calcInds() {
    inds.push_back(Elem(0, 1, 2));
    inds.push_back(Elem(0, 2, 3));
}















