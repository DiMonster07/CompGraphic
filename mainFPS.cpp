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

using namespace std;

const GLfloat WT = 800;
const GLfloat HT = 600;

char VertexShaderName[] = "VS.txt";
char FragmentShaderName[] = "FS.txt";
char TextureName[] = "mine.png";

bool is_key_press[128];

GLuint *vertexArrays;
GLuint texture1;
GLuint dirLightColor;
GLuint dirLightIntensity;
GLint attribArray;

Program ShaderProgram;
GLuint VBOcube, VAOcube, VAOgrid, VBOgrid;

Program CreateShaderProgram();
void CreateVertexBuffer();
void Render();

//GRID
const int count_vertices = 806;
float grid_vertices[count_vertices * 3];
void add_vertex(int i, float x, float y, float z);
void gen_grid();

Camera camera(70.0f, WT, HT, 0.1f, 400.0f);

void press_keys(unsigned char key, int x, int y)
{
    is_key_press[key] = true;
    camera.key_callback(is_key_press);
    glutPostRedisplay();
}

void up_keys(unsigned char key, int x, int y)
{
	is_key_press[key] = false;
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

    //setCamera(position, target, up)
    camera.setCamera(glm::vec3(25.0f, 50.0f, -45.0f), glm::vec3(-0.5f, -1.5f, 1.0f), glm::vec3(0.0f, 1.0f,  0.0f));

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

	glGenVertexArrays(1, &VAOgrid);
	glBindVertexArray(VAOgrid);

    glGenBuffers(1, &VBOgrid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOgrid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count_vertices * 3, &grid_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    //LIGHT
    camera.set_light_param(glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);

	dirLightColor = glGetUniformLocation(ShaderProgram.programId, "gDirLight.color");
    dirLightIntensity = glGetUniformLocation(ShaderProgram.programId, "gDirLight.intensity");

    /////
	glClearColor(0.9f, 0.9f, 0.9f, 0.5f);
	glutKeyboardFunc(press_keys);
	glutKeyboardUpFunc(up_keys);
	glutMainLoop();
	return 0;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(ShaderProgram.programId, "ourTexture"), 0);

	glUseProgram(ShaderProgram.programId);

    glUniform3f(dirLightColor, camera.light.color.x, camera.light.color.y, camera.light.color.z);
    glUniform1f(dirLightIntensity,  camera.light.intensity);

	GLint mvpLoc = glGetUniformLocation(ShaderProgram.programId, "mvp");
	glm::mat4 mvp = camera.get_mat();

	glBindVertexArray(VAOcube);
	glm::mat4 model;
    mvp = mvp * model;
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(VAOgrid);
    glDrawArrays(GL_LINES, 0, count_vertices);

	glUseProgram(0);
	glBindVertexArray(0);
	glutSwapBuffers();
}

void CreateVertexBuffer()
{
	GLfloat cube_vertices[] =
	{
		-10.5f, -10.5f, -10.5f,  0.0f, 0.0f,
		 10.5f, -10.5f, -10.5f,  1.0f, 0.0f,
		 10.5f,  10.5f, -10.5f,  1.0f, 1.0f,
		 10.5f,  10.5f, -10.5f,  1.0f, 1.0f,
		-10.5f,  10.5f, -10.5f,  0.0f, 1.0f,
		-10.5f, -10.5f, -10.5f,  0.0f, 0.0f,

		-10.5f, -10.5f,  10.5f,  0.0f, 0.0f,
		 10.5f, -10.5f,  10.5f,  1.0f, 0.0f,
		 10.5f,  10.5f,  10.5f,  1.0f, 1.0f,
		 10.5f,  10.5f,  10.5f,  1.0f, 1.0f,
		-10.5f,  10.5f,  10.5f,  0.0f, 1.0f,
		-10.5f, -10.5f,  10.5f,  0.0f, 0.0f,

		-10.5f,  10.5f,  10.5f,  1.0f, 0.0f,
		-10.5f,  10.5f, -10.5f,  1.0f, 1.0f,
		-10.5f, -10.5f, -10.5f,  0.0f, 1.0f,
		-10.5f, -10.5f, -10.5f,  0.0f, 1.0f,
		-10.5f, -10.5f,  10.5f,  0.0f, 0.0f,
		-10.5f,  10.5f,  10.5f,  1.0f, 0.0f,

		 10.5f,  10.5f,  10.5f,  1.0f, 0.0f,
		 10.5f,  10.5f, -10.5f,  1.0f, 1.0f,
		 10.5f, -10.5f, -10.5f,  0.0f, 1.0f,
		 10.5f, -10.5f, -10.5f,  0.0f, 1.0f,
		 10.5f, -10.5f,  10.5f,  0.0f, 0.0f,
		 10.5f,  10.5f,  10.5f,  1.0f, 0.0f,

		-10.5f, -10.5f, -10.5f,  0.0f, 1.0f,
		 10.5f, -10.5f, -10.5f,  1.0f, 1.0f,
		 10.5f, -10.5f,  10.5f,  1.0f, 0.0f,
		 10.5f, -10.5f,  10.5f,  1.0f, 0.0f,
		-10.5f, -10.5f,  10.5f,  0.0f, 0.0f,
		-10.5f, -10.5f, -10.5f,  0.0f, 1.0f,

		-10.5f,  10.5f, -10.5f,  0.0f, 1.0f,
		 10.5f,  10.5f, -10.5f,  1.0f, 1.0f,
		 10.5f,  10.5f,  10.5f,  1.0f, 0.0f,
		 10.5f,  10.5f,  10.5f,  1.0f, 0.0f,
		-10.5f,  10.5f,  10.5f,  0.0f, 0.0f,
		-10.5f,  10.5f, -10.5f,  0.0f, 1.0f
	};
	glGenBuffers(1, &VBOcube);
	glBindBuffer(GL_ARRAY_BUFFER, VBOcube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices, GL_STATIC_DRAW);
}

void add_vertex(int i, float x, float y, float z)
{
	grid_vertices[3 * i] = x;
	grid_vertices[3 * i + 1] = y;
	grid_vertices[3 * i + 2] = z;
};

void gen_grid()
{
	int j = 0;
	for (int i = -200; i <= 200; i += 10, j += 4)
	{
		add_vertex(j, i, 0, -200);
		add_vertex(j + 1, i, 0, 200);
		add_vertex(j + 2, -200, 0, i);
		add_vertex(j + 3, 200, 0, i);
	}
	add_vertex(j, 0, 0, 0);
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
