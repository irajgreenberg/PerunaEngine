#version 410 core

in vec4 vertCol; // orig attribute color set in v. shader
in vec3 vertNorm; // orig attribute vertex normal set in v. shader
out vec4 color;

vec3 vColor = vec3(1.0, 1.0, 1.0);
vec3 vDirection = vec3(-.75, 1.5, 1.0);

void main(){
    float ambience = 1.0;
    float diffuse = max(0.0, dot( normalize(vertNorm), -vDirection) );
    color = vertCol * vec4(vColor*(ambience+diffuse), 1.0);
}