#ifndef GLFW_SHADER_h
#define GLFW_SHADER_h

#if defined(_WIN32) || defined(_WIN64)
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#define GLFW_INCLUDE_GLCOREARB
#endif

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>



class Shader {
public:
	Shader();
	Shader(const std::string& vShader, const std::string& fShader);

	void init();
	void bind();
	void unbind();

	GLuint getID();
	const GLuint static getID_2();
	GLuint shader_id;

	// encapsulate passing shader loacations 
	// for attribute and uniform vars
	void addAttribute(std::string name);
	void addUniform(std::string name);


	static void setVertexShader(const std::string& vShaderURL);
	static void setFragmentShader(const std::string& fShaderURL);
	void setShaders(const std::string& vShaderURL, const std::string& fShaderURL);

	bool   isLinked();

	void   bindAttribLocation(GLuint location, const char * name);
	void   bindFragDataLocation(GLuint location, const char * name);

	void   printActiveUniforms();
	void   printActiveAttribs();


private:
	// must initialize these before using!!!
	std::string vShader, fShader;
	GLuint shader_vp;
	GLuint shader_fp;
	GLuint shader_gp;
	void printLog(GLuint program);

	// vector for attribute and uniform locations
	std::vector<GLuint> attribLocs, uniformLocs;

	// used for access in Geom3 class
	// Shader object is essentily a singleton, so the id will remain unchanged throughout program
	static GLuint shader_id_2;


	// load string
	static std::string load(const char* data);
	static const std::string load(std::string str);
};

inline GLuint Shader::getID() {
	return shader_id;
}

inline const GLuint Shader::getID_2() {
	return shader_id_2;
}

inline void Shader::bind() {
	std::cout << "in Shader::bind()" << std::endl;
	glUseProgram(shader_id);
}

inline void Shader::unbind() {
	std::cout << "in Shader::unbind()" << std::endl;
	glUseProgram(0);
}

inline void Shader::setShaders(const std::string& vShaderURL, const std::string& fShaderURL){
	vShader = vShaderURL;
	fShader = fShaderURL;
	init();
}

#endif //GLFW_SHADER_h

