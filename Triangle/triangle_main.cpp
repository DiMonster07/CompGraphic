#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>


#define caption ("TestTriangle")

using namespace std;

const int WT = 640;
const int HT = 480;

char VertexShaderName[] = "VS.txt";
char FragmentShaderName[] = "FS.txt";

GLuint triangleShaderProgram;
GLuint *vertexArrays;
GLuint *buffer;
GLint attribArray;

float triangleVertices[] =
{
	-0.9f, -0.9f, -0.5f,
	0.0f, 0.9f, -0.5f,
	0.9f, -0.9f, -0.5f,
};

GLint CreateShader(char *fileName, GLenum shaderType);
GLuint CreateShaderProgram();
void Render();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WT, HT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(caption);
	glutDisplayFunc(Render);
	glewExperimental = GL_TRUE;
	glewInit();
	triangleShaderProgram = CreateShaderProgram();
	vertexArrays = new GLuint[1];
	glGenVertexArrays(1, vertexArrays);
	buffer = new GLuint[1];
	glGenBuffers(1, buffer);
	attribArray = glGetAttribLocation(triangleShaderProgram, "vertexPosition");
	glEnableVertexAttribArray(attribArray);
	glClearColor(0.2f, 0.3f, 0.4f, 0.0f);
	glutMainLoop();
	return 0;
}

GLint CreateShader(char *fileName, GLenum shaderType)
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
	GLint shaderId = glCreateShader(shaderType);
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
	return shaderId;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(triangleShaderProgram);
	glBindVertexArray(vertexArrays[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), triangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(attribArray);
	glVertexAttribPointer(attribArray, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);
	glutSwapBuffers();
}

GLuint CreateShaderProgram()
{
	GLint vertexShader = CreateShader(VertexShaderName, GL_VERTEX_SHADER);
	GLint fragmentShader = CreateShader(FragmentShaderName, GL_FRAGMENT_SHADER);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	return shaderProgram;
}

