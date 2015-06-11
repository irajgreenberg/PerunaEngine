#version 410 core

in vec3 vert; // orig attribute vertex set in v. shader
in vec3 vertNorm; // orig attribute vertex normal set in v. shader
in vec4 vertCol; // orig attribute color set in v. shader

out vec4 finalColor;

vec4 ltCol = vec4(0.0, 0.2, 0.0, 1.0);
vec3 ltPos = vec3(0.0, 0.0, 1.0);

void main(){
    vec3 L = normalize(-ltPos);
    vec3 E = normalize(-vert); // Eye Pos is (0,0,0)
    vec3 R = normalize(-reflect(L,vertNorm));

    // materials
    vec4 diffuseMaterial = vec4(.65, .45, .5, 1.0);
    vec4 specularMaterial = vec4(1.0, 1.0, 1.0, 1.0);
    float shininess = 103.0;
    
    vec4 ambience = vec4(.1, .1, .6, 1.0);
    
    // diffusion
    vec4 diffuse = diffuseMaterial * max(0.0, dot(vertNorm, L));
    diffuse = clamp(diffuse, 0.0, 1.0);
    
    // specularity
    vec4 specular = specularMaterial * pow(max(dot(R,E),0.0),0.3*shininess);
    specular = clamp(specular, 0.0, 1.0);
    
    // Composite Color:
    finalColor = ltCol + vertCol + ambience + diffuse + specular;
}
