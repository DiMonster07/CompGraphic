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
#include "object.h"
#include "meta.h"

#define caption ("Camera")

using namespace std;

const GLfloat WT = 1200;
const GLfloat HT = 800;

char VertexShaderName[] = "VS.txt";
char FragmentShaderName[] = "FS.txt";
char TextureName[] = "mine.png";

bool is_key_press[128];

GLuint *vertexArrays;
GLuint texture1;

GLint attribArray;
GLint gWorldLoc, mvpLoc;

Object cube;

Program ShaderProgram;
GLuint VAOgrid, VBOgrid;

Program CreateShaderProgram();
void initCube();
void Render();

//GRID
const int count_vertices = 806;
float grid_vertices[count_vertices * 3];
void add_vertex(int i, float x, float y, float z);
void gen_grid();
void mInit();
void press_keys(unsigned char key, int x, int y);
void up_keys(unsigned char key, int x, int y);
void calcNormals(const unsigned int* pIndices, unsigned int IndexCount, Vertex* pVertices, unsigned int VertexCount);
Camera camera(70.0f, WT, HT, 0.1f, 600.0f);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    mInit();
    camera.setCamera(
                     glm::vec3(25.0f, 50.0f, -45.0f), //position
                     glm::vec3(-0.5f, -1.5f, 1.0f),   //target
                     glm::vec3(0.0f, 1.0f,  0.0f)     //up
                    );
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

    initCube();
    glBindVertexArray(cube.VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

	glGenVertexArrays(1, &VAOgrid);
	glBindVertexArray(VAOgrid);

    glGenBuffers(1, &VBOgrid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOgrid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count_vertices * 3, &grid_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    mvpLoc = glGetUniformLocation(ShaderProgram.programId, "mvp");
	gWorldLoc = glGetUniformLocation(ShaderProgram.programId, "gWorld");

    //LIGHT

    camera.set_light_param(glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, glm::vec3(0.0f, 0.0f, 1.0f), 0.75f);
    camera.getUniforms(ShaderProgram.programId);

    /////

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
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

	glm::mat4 gWorld = camera.get_mat();
    glUniformMatrix4fv(gWorldLoc, 1, GL_FALSE, glm::value_ptr(gWorld));

    glUniform3f(camera.dirLightColor, camera.light.color.x, camera.light.color.y, camera.light.color.z);
    glUniform1f(camera.dirLightIntensity,  camera.light.ambient_intensity);
    glm::vec3 direction = glm::normalize(camera.light.direction);
    glUniform3f(camera.dirLightDirection, camera.light.direction.x, camera.light.direction.y, camera.light.direction.z);
    glUniform1f(camera.dirLightDiffuseIntensity,  camera.light.diffuse_intensity);

    glUniform3f(camera.EyeWorldPos, camera.position.x, camera.position.y, camera.position.z);
    glUniform1f(camera.MatSpecularIntensityLoc, 1.0f);
    glUniform1f(camera.SpecularPowerLoc, 64.0f);

	glm::mat4 mvp = camera.get_mat();

    ////////////CUBE//////////////////////

	glBindVertexArray(cube.VAO);
	glm::mat4 model;
    mvp = mvp * model;
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    ///////////////////////////////////////

    glBindVertexArray(VAOgrid);
    glDrawArrays(GL_LINES, 0, count_vertices);

	glUseProgram(0);
	glBindVertexArray(0);
	glutSwapBuffers();
}

void initCube()
{
	calcNormals(cube_indices, 36, cube_vertices, 24);
	cube.GenBuffers(cube_indices, 36, cube_vertices, 24);
}

void calcNormals(const unsigned int* pIndices, unsigned int IndexCount, Vertex* pVertices, unsigned int VertexCount)
{
    for (unsigned int i = 0; i < IndexCount; i += 3)
    {
        unsigned int Index0 = pIndices[i];
        unsigned int Index1 = pIndices[i + 1];
        unsigned int Index2 = pIndices[i + 2];
        glm::vec3 v1 = pVertices[Index1].pos - pVertices[Index0].pos;
        glm::vec3 v2 = pVertices[Index2].pos - pVertices[Index0].pos;
        glm::vec3 normal = glm::cross(v2, v1);
        normal = glm::normalize(normal);
        pVertices[Index0].normal += normal;
        pVertices[Index1].normal += normal;
        pVertices[Index2].normal += normal;
    }
    for (unsigned int i = 0; i < VertexCount; i++)
        pVertices[i].normal = glm::normalize(pVertices[i].normal);
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

void mInit()
{
	glutInitWindowSize(WT, HT);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(caption);
	glutDisplayFunc(Render);
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);
	glewExperimental = GL_TRUE;
	glewInit();
}
