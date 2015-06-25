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
#endif

#if defined(__APPLE__)
//#include <OpenGL/glu.h>
#include "GLFW/glfw3.h"
// use GL3 context (OpenGL 3.2-4.1) // required for osx only, I think
#define GLFW_INCLUDE_GLCOREARB
#endif

#include "Shader.h"
#include "Cube.h"
#include "Toroid.h"
#include "Plane.h"

// for matrices
#include "glm/gtc/type_ptr.hpp" // matrix copying
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include <stack>



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


// MATRICES
// model, view, modelView, projection, modelViewProjection
glm::mat4 M, V, MV, P, MVP;
glm::mat3 N;
// translate, rotate, scale
glm::mat4 T, R, S;

// UNIFORMS for MATRICES
GLuint M_U, V_U, MV_U, P_U, MVP_U;
GLuint N_U;
GLuint T_U, R_U, S_U;

// ADS Lighting Model
glm::vec4 lightPosition;
glm::vec3 lightIntensity;
glm::vec3 lightAmbient;
glm::vec3 lightDiffuse;
glm::vec3 lightSpecularity;
float lightShininess;

// UNIFORMS for ADS lighting model
GLuint LT_POS_U, LT_INT_U, LT_AMB_U, LT_DIF_U, LT_SPEC_U, LT_SHIN_U;

float viewAngle = 75.0f;
float aspect;
float nearDist = .1;
float farDist = 500;

// function prototypes
void initUniforms(Shader* s);
void translate(glm::vec3 v);
void rotate(float ang, glm::vec3 axes);
void scale(glm::vec3 sclFactor);
void concat();

//manage transforms
void pushMatrix();
void popMatrix();
std::stack <glm::mat4> matrixStack;

// create a cube of cubes
static const int ROWS = 4;
static const int COLUMNS = 4;
static const int LAYERS = 4;
float columnWidth = 3;
float rowHeight = 3;
float layerDepth = 3;
float columnGap, rowGap, layerGap;

float zoomFactor;

int main(void) {
    
#if defined (_WIN32) || defined(_WIN64)
    glewExperimental = GL_TRUE;
#endif
    
    
    if (!glfwInit()){
        exit(EXIT_FAILURE);
    }
    
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    
#if defined (_WIN32) || defined(_WIN64)
    Shader* s = new Shader("simpleShader01.vert", "simpleShader01.frag");
#else
    Shader* s = new Shader("/Users/33993405/dev/GLFW_Demo/simpleShader01.vert", "/Users/33993405/dev/GLFW_Demo/simpleShader01.frag");
#endif
    
    
    // set up lighting
    lightPosition = glm::vec4(-6, -12, 30, 1.0);
    lightIntensity = glm::vec3(1.0, 1.0, 1.0);
    lightAmbient = glm::vec3(.2, .2, .33);
    lightDiffuse = glm::vec3(1, 1, 1);
    lightSpecularity = glm::vec3(1.0, .925, 1.0);
    lightShininess = 95;
    
    
    // generate ground plane using cube
    glm::vec4 cols[] = {
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 0.0, 1.0),
        glm::vec4(0.0, 0, 1.0, 1.0),
        glm::vec4(1.0, 1.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 1.0, 1.0, 1.0),
        glm::vec4(1.0, 0.5, 0.0, 1.0),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
    };
    
    for(int i=0; i<8; ++i){
        cols[i] = glm::vec4(.3+i*.1, .3, .3, 1.0);
        //cols[i] = glm::vec4(.2, .2, .2, 1.0);
    }

#if defined (_WIN32) || defined(_WIN64)
    std::string diffuseImg = "corroded_metal.jpg";
#else
    std::string diffuseImg = "/Users/33993405/dev/GLFW_Demo/corroded_metal.jpg";
#endif
    //Cube ground(cols, diffuseImg);
    
    Plane ground(glm::vec4(1, 1, 1, 1), diffuseImg);
    
#if defined (_WIN32) || defined(_WIN64)
    diffuseImg = "metal_grate.jpg";
#else
    diffuseImg = "/Users/33993405/dev/GLFW_Demo/metal_grate.jpg";
#endif
    Toroid toroid(1, .45, 36, 36, glm::vec4(.75, .75, .85, 1.0), diffuseImg);
    
    // initialize view matrices
    glViewport(0, 0, 640, 480);
    
    // START standard transformation matrices: ModelView / Projection / Normal
    M = glm::mat4(1.0f); // set to identity
    // eye, center, up axis
    V = glm::lookAt(glm::vec3(0.0, 0.0, 3.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    MV = V * M;
    N = glm::transpose(glm::inverse(glm::mat3(MV)));
    
    // projection matrix and MVP Matrix
    // perspective
    viewAngle = 75.0f;
    aspect = float(width) / float(height);
    
    P = glm::perspective(viewAngle, aspect, nearDist, farDist);
    MVP = P * MV;
    // END Model / View / Projection data
    
    // tranformation matricies
    T = glm::mat4(1.0f);
    R = glm::mat4(1.0f);
    S = glm::mat4(1.0f);
    s->bind();
    
    initUniforms(s);
    
    // set up vals for cube of cubes
    columnGap = columnWidth / (COLUMNS-1);
    rowGap = rowHeight / (ROWS-1);
    layerGap = layerDepth / (LAYERS-1);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int w = 0;
        int h = 0;
        glfwGetFramebufferSize(window, &w, &h);
        
        // set viewport using actual resolution independent screen size
        glViewport(0, 0, w, h);
        
        
        // reset to identity each frame
        M = glm::mat4(1.0f);
        V = glm::lookAt(glm::vec3(0.0, 0.0, 20), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
        MV = V * M;
        //mat4 normalMatrix = transpose(inverse(modelView));
        N = glm::transpose(glm::inverse(glm::mat3(MV)));
        MVP = P * MV;
        
        // update matrices
        glUniformMatrix4fv(M_U, 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
        glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(N_U, 1, GL_FALSE, &N[0][0]);
        
        // update lighting model
        glUniform4fv(LT_POS_U, 1, &lightPosition[0]);
        glUniform3fv(LT_INT_U, 1, &lightIntensity[0]);
        glUniform3fv(LT_AMB_U, 1, &lightAmbient[0]);
        glUniform3fv(LT_DIF_U, 1, &lightDiffuse[0]);
        glUniform3fv(LT_SPEC_U, 1, &lightSpecularity[0]);
        glUniform1f(LT_SHIN_U, lightShininess);
        
        // global transforms
        pushMatrix();
        translate(glm::vec3(0, -5, 0));
        scale(glm::vec3(200, 1, 200));
        ground.display();
        popMatrix();
        
        //rotate(-glfwGetTime()*.1, glm::vec3(-.35, 1, .1));
        
//        for(int i=0; i<COLUMNS; ++i){
//            for(int j=0; j<ROWS; ++j){
//                for(int k=0; k<LAYERS; ++k){
//                    pushMatrix();
//                    translate(glm::vec3(-columnWidth/2+columnGap*i, -rowHeight/2+rowGap*j, -layerDepth/2+layerGap*k));
//                    rotate(-glfwGetTime(), glm::vec3(-.35, 1, .1));
//                    scale(glm::vec3(2.55, 2.55, 2.55));
//                    ground.display();
//                    popMatrix();
//                }
//            }
//        }
        
        pushMatrix();
        translate(glm::vec3(0, 0, -8));
        rotate(-glfwGetTime(), glm::vec3(.65, 1, .345));
        scale(glm::vec3(2.55, 2.55, 2.55));
        toroid.display();
        popMatrix();
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    
}

void initUniforms(Shader* s){
    // std::cout << "s->shader_id = " << s->shader_id << std::endl;
    // set variable name of uniforms in shader
    M_U = glGetUniformLocation(s->shader_id, "modelMatrix");
    MV_U = glGetUniformLocation(s->shader_id, "modelViewMatrix");
    MVP_U = glGetUniformLocation(s->shader_id, "modelViewProjectionMatrix");
    N_U = glGetUniformLocation(s->shader_id, "normalMatrix");
    
    // lighting
    // ADS Lighting Model uniforms
    LT_POS_U = glGetUniformLocation(s->shader_id, "lightPos");
    LT_INT_U = glGetUniformLocation(s->shader_id, "lightInt");
    LT_AMB_U = glGetUniformLocation(s->shader_id, "amb");
    LT_DIF_U = glGetUniformLocation(s->shader_id, "diff");
    LT_SPEC_U = glGetUniformLocation(s->shader_id, "spec");
    LT_SHIN_U = glGetUniformLocation(s->shader_id, "shin");
}

// TCRANSFORMAION Functions
void translate(glm::vec3 v) {
    M = glm::translate(M, v);
    concat();
}

void rotate(float ang, glm::vec3 axes) {
    M = glm::rotate(M, ang, axes);
    concat();
}

void scale(glm::vec3 sclFactor) {
    M = glm::scale(M, sclFactor);
    concat();
}

// rebuild transformed MVP matrix and update shader uniforms
void concat(){
    MV = V * M;
    //gl_NormalMatrix= glm::transpose(glm::inverse(glm::mat3(gl_ModelViewMatrix)));
    N = glm::transpose(glm::inverse(glm::mat3(MV)));
    MVP = P * MV;
    glUniformMatrix4fv(M_U, 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(MV_U, 1, GL_FALSE, &MV[0][0]);
    glUniformMatrix4fv(MVP_U, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(N_U, 1, GL_FALSE, &N[0][0]);
}

// implements transform matrix stack
void pushMatrix(){
    // push current transformation matrix onto stack
    matrixStack.push(M);
    
}

// reset transformation matrix with stored matrix on stack
void popMatrix(){
    
    // reset current transformation matrix with one on top of stack
    M = matrixStack.top();
    
    // pop transformation matrix off top of stack
    matrixStack.pop();
    
    // rebuild matrices and update on GPU
    concat();
}

