#if defined(_WIN32) || defined(__linux__)
#include <GL/glew.h>
#else
#include <OpenGL/gl.h>
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
	Shader(const Shader& shdr);
	Shader& operator=(const Shader& shdr);
	~Shader();

	void init();

	void bind();
	void unbind();

	GLuint getID();
	GLuint shader_id;

	// encapsulate passing shader loacations 
	// for attribute and uniform vars
	void addAttribute(std::string name);
	void addUniform(std::string name);

	const GLuint static getID_2();
	static void setVertexShader(const std::string& vShaderURL);
	static void setFragmentShader(const std::string& fShaderURL);
	static void setGeometryShader(const std::string& gShaderURL);
	void setShaders(const std::string& vShaderURL, const std::string& fShaderURL);

	/******/#define setVertShader setVertexShader;
	/******/#define setFragShader setFragmentShader;
	/******/#define setGeomShader setGeometryShader;

	bool   isLinked();

	void   bindAttribLocation(GLuint location, const char * name);
	void   bindFragDataLocation(GLuint location, const char * name);


	// from Opengl 4.0 Cookbook
	//void   setUniform(const char *name, const glm::vec3 & v);
	//void   setUniform(const char *name, const glm::vec4 & v);
	//void   setUniform(const char *name, const glm::mat4 & m);
	//void   setUniform(const char *name, const glm::mat3 & m);
	//void   setUniform(const char *name, float val);
	//void   setUniform(const char *name, int val);
	//void   setUniform(const char *name, bool val);

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

};