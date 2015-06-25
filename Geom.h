//
//  Base class for all geometry
//  Geom.h
//  GLFW_Demo
//
//  Created by Ira on 6/3/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#ifndef __GLFW_Demo__Geom__
#define __GLFW_Demo__Geom__

#if defined (_WIN32) || defined(_WIN64)
#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include<gl/gl.h>
#include<gl/glu.h>
#endif

#if defined(__APPLE__)
#define glGenVertexArraysAPPLE glGenVertexArrays
#define glBindVertexArrayAPPLE glBindVertexArray
#include <OpenGL/glu.h>
#include "GLFW/glfw3.h"
#endif


#include <stdio.h>
#include <vector>
#include <iostream>
#include "Elem.h"
#include "Face.h"
#include "glm/glm.hpp"
#include "ProtoTexture.h"
#include "Shader.h"



#define BUFFER_OFFSET(i) ((void*)(i))

class Geom {
    
public:
	enum renderMode {
		SURFACE,
		WIREFRAME,
		POINT
	};

	Geom();
	void display(renderMode mode = SURFACE);


private:

	enum { STRIDE = 12 };
	std::vector<float> interleavedPrims;
	std::vector<unsigned int> indPrims;

	// Buffer control
	// VAO
	GLuint vaoID;
	// VBO stuff
	GLuint vboID, indexVboID;

    void calcVertexNorms();
    void calcPrimitives();
    void createBuffers();
    
   
	
   

protected:
    
    std::vector<glm::vec3> verts;
    std::vector<glm::vec3> vertNorms;
    std::vector<glm::vec4> cols;
    std::vector<glm::vec2> uvs;
    std::vector<Elem> inds;
    std::vector<Face> faces;
    
    GLint diffuseMapLoc;
    ProtoTexture diffuseMapTexture;
    void createDiffuseMapTexture(const std::string& diffuseMapImage);
    //std::string diffuseMapImage;
    
    
    void calcFaces();
    virtual void init();
    
    virtual void calcVerts() = 0;
    virtual void calcInds() = 0;
};

#endif /* defined(__GLFW_Demo__Geom__) */











