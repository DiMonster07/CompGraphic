#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


struct Matrix4f
{
    float m[4][4];
};

class Shader
{
public:
	GLuint shaderId;
	Shader(const char *fileName, GLenum shaderType)
	{
		FILE* infile;
		infile = fopen(fileName, "rb");
		fseek(infile, 0, SEEK_END);
		int fSize = ftell(infile);
		rewind(infile);
		char* text = (char*)malloc(sizeof(char) * fSize);
		fread(text, 1, fSize, infile);
		fclose(infile);
		const GLint shaderLength[1] = {fSize};
		GLchar *textBuffer = text;
		const GLchar *shaderText[1] = {textBuffer};
		shaderId = glCreateShader(shaderType);
		glShaderSource(shaderId, 1, shaderText, shaderLength);
		delete [] textBuffer;
		glCompileShader(shaderId);
		GLint is_compiled;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &is_compiled);
		if (!is_compiled)
		{
			GLint log_length = 0;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &log_length);
			GLchar *info_log = new GLchar[log_length];
			GLint returned_length = 0;
			glGetShaderInfoLog(shaderId, log_length, &returned_length, info_log);
			glDeleteShader(shaderId);
			cout << "Shader compilation error in " << fileName;
			cout << '\n' << info_log;
			delete [] info_log;
			exit(0);
		}
	}
};

class Program
{
public:
	GLuint programId, attribArray, mvp;

	Program()
	{
		GLuint programId = 0;
		GLint  attribArray = 0;
	}

	Program(const Shader &shader1, const Shader &shader2)
	{
		programId = glCreateProgram();
		glAttachShader(programId, shader1.shaderId);
		glAttachShader(programId, shader2.shaderId);
		glLinkProgram(programId);
		GLint isLinkSuccesful;
		glGetProgramiv(programId, GL_LINK_STATUS, &isLinkSuccesful);
		if (!isLinkSuccesful) {
			GLint log_length = 0;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &log_length);
			GLchar *info_log = new GLchar[log_length];
			GLint returned_length = 0;
			glGetProgramInfoLog(programId, log_length, &returned_length, info_log);
			cout << "Program linking error\n" << info_log;
			glDeleteProgram(programId);
			delete [] info_log;
			exit(0);
		}
	}

	void AttachShader(const char *fileName, GLenum shaderType) {
		glAttachShader(programId, Shader(fileName, shaderType).shaderId);
	}

	void Link() {
		glLinkProgram(programId);
	}
};

