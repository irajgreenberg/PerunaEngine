//
//  main.cpp
//  GLFW_Demo
//
//  Created by Ira on 6/2/15.
//  Copyright (c) 2015 C3. All rights reserved.
//

#if defined (_WIN32) || defined(_WIN64)
#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "Shader.h"
#include "Cube.h"
#endif

#if defined(__APPLE__)
#include <OpenGL/glu.h>
#include "GLFW/glfw3.h"
#endif

// for matrices
#include "glm/gtc/type_ptr.hpp" // matrix copying
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"




static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


float width = 640, height = 480;
Cube* cube;

// shader
Shader s;

// MATRICES
// model, view, modelView, projection, modelViewProjection
glm::mat4 M, V, MV, P, MVP;
// translate, rotate, scale
glm::mat4 T, R, S;

// UNIFORMS for MATRICES
GLuint M_U, V_U, MV_U, P_U, MVP_U;
GLuint T_U, R_U, S_U;
// function prototype
void initUniforms();

float viewAngle = 75.0f;
float aspect;




int main(void)
{
    

	
	glewExperimental = GL_TRUE;
	if (!glfwInit()){
		exit(EXIT_FAILURE);
	}

	


	GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);


	
	s = Shader("simpleShader01.vert", "simpleShader01.frag");
	cube = new Cube();

	// initialize view matrices
	glViewport(0, 0, 640, 480);

	// START standard transformation matrices: ModelView / Projection / Normal
	M = glm::mat4(1.0f); // set to identity
	V = glm::lookAt(glm::vec3(0.0, 0.0, 2.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	MV = V * M;

	// projection matrix and MVP Matrix
	// perspective
	viewAngle = 75.0f;
	aspect = float(width) / float(height);
	//// ortho
	////trace("width = ", width);
	////trace("height =", height);
	//left = -width / 2;
	//right = width / 2;
	//bottom = -height / 2;
	//top = height / 2;

	//nearDist = .1f;
	//farDist = 1500.0f;

	P = glm::perspective(viewAngle, aspect, .1f, 1000.0f);
	MVP = P * MV;
	// END Model / View / Projection data

	// tranformation matricies
	T = glm::mat4(1.0f);
	R = glm::mat4(1.0f);
	S = glm::mat4(1.0f);
	s.bind();

	initUniforms();


    while (!glfwWindowShouldClose(window))
    {
        float ratio;
       // int width, height;
       // glfwGetFramebufferSize(window, &width, &height);
       // ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
		glUniformMatrix4fv(M_U, 1, GL_FALSE, &M[0][0]);
		glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
		glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
		//for (int i = 0; i < 4; i++){
		//	for (int j = 0; j < 4; j++){
		//		std::cout << "MVP["<<i<<"]["<<j<<"] = " << MVP[i][j] << std::endl;
		//	}
		//}
        //glMatrixMode(GL_PROJECTION);
        //glLoadIdentity();
        //glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //glMatrixMode(GL_MODELVIEW);
        //glLoadIdentity();
        //glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        //glBegin(GL_TRIANGLES);
        //glColor3f(1.f, 0.f, 0.f);
        //glVertex3f(-0.6f, -0.4f, 0.f);
        //glColor3f(0.f, 1.f, 0.f);
        //glVertex3f(0.6f, -0.4f, 0.f);
        //glColor3f(0.f, 0.f, 1.f);
        //glVertex3f(0.f, 0.6f, 0.f);
        //glEnd();
		cube->display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void initUniforms(){
	// set variable name of uniforms in shader
	M_U = glGetUniformLocation(s.shader_id, "modelMatrix");
	MV_U = glGetUniformLocation(s.shader_id, "modelViewMatrix");
	MVP_U = glGetUniformLocation(s.shader_id, "modelViewProjectionMatrix");
}
