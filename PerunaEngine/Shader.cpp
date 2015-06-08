#include "Shader.h"


// initialize static shaderID
GLuint Shader::shader_id_2 = 0;

Shader::Shader() {
}

Shader::Shader(const std::string& vShader, const std::string& fShader) :
vShader(vShader), fShader(fShader){
	init();
}

void Shader::init() {

	// initialize glew for Windows
#if defined(_WIN32) || defined(_win64)
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

	std::string vShaderCodeStr = load(vShader);
	std::string fShaderCodeStr = load(fShader);


	const GLchar* vShaderCode = vShaderCodeStr.c_str();
	const GLchar* fShaderCode = fShaderCodeStr.c_str();


	if (vShaderCode == NULL || fShaderCode == NULL) {
		std::cerr << "Either vertex shader or fragment shader file not found." << std::endl;
		return;
	}

	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	if (0 == shader_vp){
		std::cerr << "Error creating vertex shader" << std::endl;
		return;
	}

	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
	if (0 == shader_fp){
		std::cerr << "Error creating fragment shader" << std::endl;
		return;
	}

	glShaderSource(shader_vp, 1, &vShaderCode, NULL);
	glShaderSource(shader_fp, 1, &fShaderCode, NULL);

	glCompileShader(shader_vp);
	glCompileShader(shader_fp);

	//Check shader for errors
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(shader_vp, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		printf("Unable to compile Vertex shader %d!\n\nSource:\n%s\n", shader_vp, vShaderCode);
		//printShaderLog( shader_vp );
		glDeleteShader(shader_vp);
		shader_vp = 0;
	}

	glGetShaderiv(shader_fp, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		printf("Unable to compile fragment shader %d!\n\nSource:\n%s\n", shader_fp, fShaderCode);
		//printShaderLog( shader_vp );
		glDeleteShader(shader_fp);
		shader_fp = 0;
	}


	shader_id = glCreateProgram();
	Shader::shader_id_2 = shader_id; // capture id value

	glAttachShader(shader_id, shader_vp);
	glAttachShader(shader_id, shader_fp);

	glLinkProgram(shader_id);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(shader_id, GL_LINK_STATUS, &programSuccess);
	//   std::cout << "programSuccess = " << programSuccess << std::endl;
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", shader_id);
		printLog(shader_id);
		glDeleteProgram(shader_id);
		shader_id = 0;
	}
	//glUseProgram(shader_id);
}


// get string from file (char* URL input)
std::string Shader::load(const char* data) {
	std::ifstream file(data);
	std::string line, block;
	if (file.is_open()) {

		while (!file.eof()) {
			std::getline(file, line);
			block.append(line);
			block.append(std::string("\n"));
		}
		file.close();
		return block;
	}
	else {
		std::cout << "Unable to open file";
	}
	// never reached - added to squelch ide warning
	return 0;
}

// get string from file (string URL input)
const std::string Shader::load(std::string data){
	const char *charData = data.c_str();
	return load(charData);
}

void Shader::printLog(GLuint program){
	int maxLength = 0;
	int length = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
	char* log = new char[maxLength];
	glGetProgramInfoLog(program, maxLength, &length, log);
	std::cout << "program log: " << log << std::endl;
}

void Shader::addAttribute(std::string name){
}
void Shader::addUniform(std::string name){
}
