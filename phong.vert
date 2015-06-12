#version 410 core

//http://www.mathematik.uni-marburg.de/~thormae/lectures/graphics1/code/WebGLShaderLightMat/ShaderLightMat.html

// accessing attributes in memory
// created on CPU side and passed into GPU
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec4 vertexColor;

// to pass color through to the Fragment shader
out vec3 vert;
out vec3 vertNorm;
out vec4 vertCol;

uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

out vec3 normalInterp;
out vec3 vertPos;

void main(){
    gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
    vec4 vertPos4 = modelViewMatrix * vec4(vertexPosition, 1.0);
    vertPos = vec3(vertPos4) / vertPos4.w;
    normalInterp = vec3(normalMatrix * vec4(vertexNormal, 0.0));
}
