// Based on the ADS (ambient, diffuse, specularity) Shading Model
// combines following light properties:
//  lightPos
//  lightInt
//  amb
//  diff
//  spec
//  shin


#version 430 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec4 vertexColor;

out vec3 eyeDir;
out vec3 lightDir;
out vec3 normal;
	

// coord transforms
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

// switch with passed in lights
uniform vec3 light_pos = vec3(-10, -10, 10);

// Lights
// max 8 lt srcs (fer now...)
struct Light {
	vec3 position;
	vec3 intensity;
};
uniform Light light;

 // to pass color through, in addition to maps
 out vec4 vertCol;

void main(void)
{
   
	vertCol = vertexColor;

	// Calculate vertex position in view space.
    vec4 P = modelViewMatrix * vec4(vertexPosition, 1.0);

    // Calculate normal in view space from
    // incoming object space vectors.
    vec3 V = P.xyz;
    vec3 N = normalize(mat3(modelViewMatrix) * vertexNormal);
   
    // The light vector (L) is the vector from the point of interest to
    // the light. Calculate that and multiply it by the TBN matrix.
		//vec3 L = light.position - P.xyz;
		vec3 L = light_pos - P.xyz;
		lightDir = normalize(vec3(dot(L, N), dot(L, N), dot(L, N)));

    // The view vector is the vector from the point of interest to the
    // viewer, which in view space is simply the negative of the position.
    V = -P.xyz;
    eyeDir = normalize(vec3(dot(V, N), dot(V, N), dot(V, N)));

    // Pass the per-vertex normal so that the fragment shader can
    // turn the normal map on and off.
   normal = N;

    // Calculate clip coordinates by multiplying our view position by
    // the projection matrix.
    gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}