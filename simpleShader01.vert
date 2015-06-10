#version 410 core

// accessing attributes in memory
// created on CPU side and passed into GPU
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec4 vertexColor;

// to pass color through to the Fragment shader
out vec4 vertCol;
out vec3 vertNorm;


uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;


void main(void) {
	vertCol = vertexColor;
    vertNorm = normalize(mat3(modelViewMatrix) * vertexNormal);
    //vertNorm = vertexNormal * mat3(normalMatrix);
    //normalMatrix;
  	gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}

