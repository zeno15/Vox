#ifndef INCLUDED_SHADER_HPP
#define INCLUDED_SHADER_HPP

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <string>

class Shader {
public:
    Shader();
	Shader(const char *_vsFile, const char *_fsFile);

    ~Shader();

	void init(const char *_vsFile, const char *_fsFile);

	void bind();
	void unbind(); 
	unsigned int id();

private:
	static const char* textFileRead(const char *_fileName);

	static void validateShader(GLuint _shader, const char* _file = 0);
	static void validateProgram(GLuint _program);

private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;
};

#endif //~ INCLUDED_SHADER_HPP