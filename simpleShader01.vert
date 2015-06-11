#version 410 core

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


void main(void) {
    //vert = vec3((modelViewMatrix) * vec4(vertexPosition, 1.0));
    vert = vertexPosition;
    vertNorm = normalize(vec3(mat3(modelViewMatrix) * vertexNormal));
    vertCol = vertexColor;
  	gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}

