#version 410 core

in vec4 vertCol; // orig attribute color set in v. shader
out vec4 color;

void main(){
	color = vertCol;
}