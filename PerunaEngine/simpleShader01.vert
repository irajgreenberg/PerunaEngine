#version 430 core

// accessing attributes in memory
// created on CPU side and passed into GPU
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec4 vertexColor;

// to pass color through to the Fragment shader
out vec4 vertCol;


uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;


void main(void) {
	vertCol = vertexColor;
  	gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}

