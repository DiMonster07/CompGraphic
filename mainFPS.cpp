#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glfw.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glprog.h"
#include "camera.h"

#define caption ("Camera")
#define LINE_AMOUNT 2*10

using namespace std;

const GLfloat WT = 800;
const GLfloat HT = 600;

char VertexShaderName[] = "VS.txt";
char FragmentShaderName[] = "FS.txt";
char TextureName[] = "mine.png";

Program ShaderProgram;
GLuint VBOcube, VAOcube, VAOgrid, VBOgrid;

Program CreateShaderProgram();
void CreateIndexBuffer();
void CreateVertexBuffer();
void Render();
void mouse_callback(int x, int y);
void key_callback(unsigned char key, int x, int y);

glm::vec3 cubePositions[] =
{
	glm::vec3( 0.0f,  0.0f,  0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3( 1.3f, -2.0f, -2.5f),
	glm::vec3( 1.5f,  2.0f, -2.5f),
	glm::vec3( 1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

GLuint *vertexArrays;
GLint attribArray;
GLuint texture1;

bool keys[1024];
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  2.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
const int count_vertices = 806;
float grid_vertices[count_vertices * 3];

void add_vertex(int i, float x, float y, float z)
{
	grid_vertices[3 * i] = x;
	grid_vertices[3 * i + 1] = y;
	grid_vertices[3 * i + 2] = z;
};

void gen_grid()
{
	int j = 0;
	for (int i = -1000; i <= 1000; i += 10, j += 4)
	{
		add_vertex(j, i, 0, -1000);
		add_vertex(j + 1, i, 0, 1000);
		add_vertex(j + 2, -1000, 0, i);
		add_vertex(j + 3, 1000, 0, i);
	}
	add_vertex(j, 0, 0, 0);
	add_vertex(j + 1, 0, 1000, 0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WT, HT);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(caption);
	glutDisplayFunc(Render);
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);
	glewExperimental = GL_TRUE;
	glewInit();

    gen_grid();
	int width = 0, height = 0;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* image = SOIL_load_image("mine.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);

	attribArray = glGetAttribLocation(ShaderProgram.programId, "position");
	ShaderProgram = CreateShaderProgram();

	glGenVertexArrays(1, &VAOcube);
	glBindVertexArray(VAOcube);

    CreateVertexBuffer();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

    //Buffer for grid

	glGenVertexArrays(1, &VAOgrid);
	glBindVertexArray(VAOgrid);

    glGenBuffers(1, &VBOgrid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOgrid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count_vertices * 3, &grid_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

    glBindVertexArray(0);

	glClearColor(0.1f, 0.3f, 0.4f, 0.0f);
	glutKeyboardFunc(key_callback);
	glutPassiveMotionFunc(mouse_callback);
	glutMainLoop();
	return 0;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(ShaderProgram.programId, "ourTexture1"), 0);
	glUseProgram(ShaderProgram.programId);

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = glm::perspective(70.0f, (GLfloat)WT / (GLfloat)HT, 0.1f, 400.0f);

	GLint modelLoc = glGetUniformLocation(ShaderProgram.programId, "model");
	GLint viewLoc = glGetUniformLocation(ShaderProgram.programId, "view");
	GLint projLoc = glGetUniformLocation(ShaderProgram.programId, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAOcube);
	for (GLuint i = 0; i < 10; i++)
    {
		model = glm::translate(model, cubePositions[i]);
		GLfloat angle = 20.0f * i;
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(VAOgrid);
    glDrawArrays(GL_LINES, 0, count_vertices);

	glUseProgram(0);
	glBindVertexArray(0);
	glutSwapBuffers();
}

void key_callback(unsigned char key, int x, int y)
{
	GLfloat cameraSpeed = 1.1f;
	switch(key)
	{
		case 'w':
			cameraPos += cameraSpeed * cameraFront;
			break;
		case 's':
			cameraPos -= cameraSpeed * cameraFront;
			break;
		case 'd':
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
		case 'a':
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
		case 27:
			exit(0);
			break;
	}
	glutPostRedisplay();
}

GLfloat yaw    = -90.0f;
GLfloat pitch  =  0.0f;
GLfloat lastX  =  WT / 2.0;
GLfloat lastY  =  HT / 2.0;
bool firstMouse = true;
void mouse_callback(int x, int y)
{
    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    GLfloat xoffset = x - lastX;
    GLfloat yoffset = lastY - y;
    lastX = x;
    lastY = y;

    GLfloat sensitivity = 0.5;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    glutPostRedisplay();
}

void CreateIndexBuffer()
{

}

void CreateVertexBuffer()
{
	GLfloat cube_vertices[] =
	{
		-1.5f, -1.5f, -1.5f,  0.0f, 0.0f,
		 1.5f, -1.5f, -1.5f,  1.0f, 0.0f,
		 1.5f,  1.5f, -1.5f,  1.0f, 1.0f,
		 1.5f,  1.5f, -1.5f,  1.0f, 1.0f,
		-1.5f,  1.5f, -1.5f,  0.0f, 1.0f,
		-1.5f, -1.5f, -1.5f,  0.0f, 0.0f,

		-1.5f, -1.5f,  1.5f,  0.0f, 0.0f,
		 1.5f, -1.5f,  1.5f,  1.0f, 0.0f,
		 1.5f,  1.5f,  1.5f,  1.0f, 1.0f,
		 1.5f,  1.5f,  1.5f,  1.0f, 1.0f,
		-1.5f,  1.5f,  1.5f,  0.0f, 1.0f,
		-1.5f, -1.5f,  1.5f,  0.0f, 0.0f,

		-1.5f,  1.5f,  1.5f,  1.0f, 0.0f,
		-1.5f,  1.5f, -1.5f,  1.0f, 1.0f,
		-1.5f, -1.5f, -1.5f,  0.0f, 1.0f,
		-1.5f, -1.5f, -1.5f,  0.0f, 1.0f,
		-1.5f, -1.5f,  1.5f,  0.0f, 0.0f,
		-1.5f,  1.5f,  1.5f,  1.0f, 0.0f,

		 1.5f,  1.5f,  1.5f,  1.0f, 0.0f,
		 1.5f,  1.5f, -1.5f,  1.0f, 1.0f,
		 1.5f, -1.5f, -1.5f,  0.0f, 1.0f,
		 1.5f, -1.5f, -1.5f,  0.0f, 1.0f,
		 1.5f, -1.5f,  1.5f,  0.0f, 0.0f,
		 1.5f,  1.5f,  1.5f,  1.0f, 0.0f,

		-1.5f, -1.5f, -1.5f,  0.0f, 1.0f,
		 1.5f, -1.5f, -1.5f,  1.0f, 1.0f,
		 1.5f, -1.5f,  1.5f,  1.0f, 0.0f,
		 1.5f, -1.5f,  1.5f,  1.0f, 0.0f,
		-1.5f, -1.5f,  1.5f,  0.0f, 0.0f,
		-1.5f, -1.5f, -1.5f,  0.0f, 1.0f,

		-1.5f,  1.5f, -1.5f,  0.0f, 1.0f,
		 1.5f,  1.5f, -1.5f,  1.0f, 1.0f,
		 1.5f,  1.5f,  1.5f,  1.0f, 0.0f,
		 1.5f,  1.5f,  1.5f,  1.0f, 0.0f,
		-1.5f,  1.5f,  1.5f,  0.0f, 0.0f,
		-1.5f,  1.5f, -1.5f,  0.0f, 1.0f
	};
	glGenBuffers(1, &VBOcube);
	glBindBuffer(GL_ARRAY_BUFFER, VBOcube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices, GL_STATIC_DRAW);
}

Program CreateShaderProgram()
{
	Shader vertexShader = Shader(VertexShaderName, GL_VERTEX_SHADER);
	Shader fragmentShader = Shader(FragmentShaderName, GL_FRAGMENT_SHADER);
	Program shaderProgram = Program(vertexShader, fragmentShader);
	glAttachShader(shaderProgram.programId, vertexShader.shaderId);
	glAttachShader(shaderProgram.programId, fragmentShader.shaderId);
	glLinkProgram(shaderProgram.programId);
	return shaderProgram;
}
