//
//  Cube.cpp
//  GLFW_Demo
//
//  Created by Ira on 6/3/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#include "Cube.h"

Cube::Cube() { 
	for (int i = 0; i < 8; ++i){
		this->cols.push_back(glm::vec4(.5, .5, .9, 1.0));
	}
    //createDiffuseMapTexture( --add string-- );
	init();
}

Cube::Cube(glm::vec4 cols[], std::string& diffuseMap){
	for (int i = 0; i < 8; ++i){
		this->cols.push_back(cols[i]);
	}
    createDiffuseMapTexture(diffuseMap);
    init();
}

// must include concrete implementations
// of abstract functions (pure virtuals)
void Cube::calcVerts() {
    verts.push_back(glm::vec3(-.5, .5, .5));
    verts.push_back(glm::vec3(-.5, -.5, .5));
    verts.push_back(glm::vec3(.5, -.5, .5));
    verts.push_back(glm::vec3(.5, .5, .5));
    verts.push_back(glm::vec3(-.5, .5, -.5));
    verts.push_back(glm::vec3(.5, .5, -.5));
    verts.push_back(glm::vec3(.5, -.5, -.5));
    verts.push_back(glm::vec3(-.5, -.5, -.5));
    
    
    uvs.push_back(glm::vec2(0, 0));
    uvs.push_back(glm::vec2(0, 1));
    uvs.push_back(glm::vec2(1, 1));
    uvs.push_back(glm::vec2(1, 0));
    uvs.push_back(glm::vec2(0, 0));
    uvs.push_back(glm::vec2(0, 1));
    uvs.push_back(glm::vec2(1, 1));
    uvs.push_back(glm::vec2(1, 0));
}

void Cube::calcInds() {
    inds.push_back(Elem(0, 1, 2));
    inds.push_back(Elem(0, 2, 3));
    inds.push_back(Elem(0, 3, 4));
    inds.push_back(Elem(3, 5, 4));
    inds.push_back(Elem(2, 6, 3));
    inds.push_back(Elem(6, 5, 3));
    inds.push_back(Elem(0, 4, 7));
    inds.push_back(Elem(0, 7, 1));
    inds.push_back(Elem(7, 2, 1));
    inds.push_back(Elem(7, 6, 2));
    inds.push_back(Elem(7, 4, 6));
    inds.push_back(Elem(6, 4, 5));
}















