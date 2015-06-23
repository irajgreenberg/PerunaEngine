#version 410 core

// accessing attributes in memory
// created on CPU side and passed into GPU
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec4 vertexColor;
layout (location = 3) in vec2 vertexUV;

// to pass color through to the Fragment shader
out vec3 position;
out vec3 normal;
out vec4 color;
out vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;


void main(void) {
    position = vec3(modelViewMatrix * vec4(vertexPosition, 0.0));
    normal = normalize(mat3(modelViewMatrix)*vertexNormal);
    color = vertexColor;
    uv = vertexUV;
  	gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}

