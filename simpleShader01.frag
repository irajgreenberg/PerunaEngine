#version 410 core

in vec4 vertCol; // orig attribute color set in v. shader
in vec3 vertNorm; // orig attribute vertex normal set in v. shader
out vec4 color;

vec3 vColor = vec3(.75, .75, .88);
vec3 vDirection = vec3(1.75, .5, 2.0);

void main(){
    float ambience = 1;
    float diffuse = max(0.0, dot( normalize(vertNorm), -vDirection) );
    color = vertCol * vec4(vColor*(ambience+diffuse), 1.0);
}