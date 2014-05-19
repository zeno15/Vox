#include "Shader.hpp"

#include <iostream>
#include <string>
#include <fstream>

Shader::Shader()
{
}

Shader::Shader(const char *_vsFile, const char *_fsFile)
{
	init(_vsFile, _fsFile);
}

Shader::~Shader()
{
	glDetachShader(shader_id, shader_fp);
	glDetachShader(shader_id, shader_vp);

	glDeleteShader(shader_fp);
	glDeleteShader(shader_vp);

	glDeleteProgram(shader_id);
}


void Shader::init(const char *_vsFile, const char *_fsFile)
{
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

	const char *vsText = textFileRead(_vsFile);
	const char *fsText = textFileRead(_fsFile);

	if (vsText == nullptr || fsText == nullptr)
	{
		std::cout << "ERROR: Either vertex or fragment shader file could not be found" << std::endl;
		return;
	}

	glShaderSource(shader_vp, 1, &vsText, 0);
	glShaderSource(shader_fp, 1, &fsText, 0);

	glCompileShader(shader_vp);
	validateShader(shader_vp, _vsFile);
	glCompileShader(shader_fp);
	validateShader(shader_fp, _fsFile);

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
	validateProgram(shader_id);

	delete vsText;
	delete fsText;
}

void Shader::bind()
{
	glUseProgram(shader_id);
}
void Shader::unbind()
{
	glUseProgram(0);
}
unsigned int Shader::id()
{
	return shader_id;
}

const char *Shader::textFileRead(const char *_fileName)
{
	std::string text;
	std::string line;

	std::ifstream file;
	file.open(_fileName);

	while (file.good())
	{
		std::getline(file, line);

		text.append(line);
		text.append("\n");

	}

	char *output = new char[text.size() + 1];

	for (unsigned int i = 0; i < text.size(); i += 1)
	{
		output[i] = text.at(i);
	}
	output[text.size()] = '\0';

	return output;
}

void Shader::validateShader(GLuint _shader, const char* _file /*= 0*/)
{
	const unsigned int BUFFER_SIZE = 512;

	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	GLsizei length = 0;

	glGetShaderInfoLog(_shader, BUFFER_SIZE, &length, buffer);

	if (length > 0)
	{
		std::cout << "ERROR: Shader " << _shader << "(" << (_file ? _file : "") << ") compile error: " << buffer << std::endl;
	}
}

void Shader::validateProgram(GLuint _program)
{
	const unsigned int BUFFER_SIZE = 512;

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    GLsizei length = 0;
    
    memset(buffer, 0, BUFFER_SIZE);
    glGetProgramInfoLog(_program, BUFFER_SIZE, &length, buffer);

	if (length > 0)
	{
		std::cout << "Program " << _program << " link error : " << buffer << std::endl;
	}
    
    glValidateProgram(_program);

    GLint status;

    glGetProgramiv(_program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cout << "Error validating shader " << _program << std::endl;
	}
}