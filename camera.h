#pragma once
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

#define KEY_W ('w')
#define KEY_A ('a')
#define KEY_S ('s')
#define KEY_D ('d')
#define KEY_U ('u')
#define KEY_H ('h')
#define KEY_J ('j')
#define KEY_K ('k')
#define KEY_Q ('q')
#define KEY_E ('e')
#define KEY_Z ('z')
#define KEY_X ('x')
#define KEY_C ('c')
#define KEY_V ('v')
#define KEY_B ('b')
#define KEY_N ('n')
#define KEY_B ('b')
#define KEY_N ('n')

#define MAX_POINT_LIGHTS 3


struct BaseLight
{
    glm::vec3 color;
    float ambientIntensity;
    float diffuseIntensity;

    BaseLight()
    {
        color = glm::vec3(0.0f, 0.0f, 0.0f);
        ambientIntensity = 0.0f;
        diffuseIntensity = 0.0f;
    }
};

struct DirectionalLight : public BaseLight
{
    glm::vec3 direction;

    DirectionalLight()
    {
        direction = glm::vec3(0.0f, 0.0f, 0.0f);
    }
};

struct PointLight : public BaseLight
{
    glm::vec3 position;

    struct
    {
        float constant;
        float linear;
        float exp;
    } attenuation;

    PointLight()
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        attenuation.constant = 1.0f;
        attenuation.linear = 0.0f;
        attenuation.exp = 0.0f;
    }
};

struct DirLight
{
    glm::vec3 color;
    float ambient_intensity;
    glm::vec3 direction;
    float diffuse_intensity;
};


class Camera
{
	public:
		Camera(GLfloat fovy, GLint width, GLint hight, GLfloat near_plane, GLfloat far_plane);
		void setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up);
		void zoom(float value);
		void rotate();
		void key_callback(bool is_key_press[128]);
		void key_callback_special(unsigned char key);
		void set_light_param(glm::vec3 color, float ambient_intensity, glm::vec3 direction, float diffuse_intensity);
		void lightRender();
		void getUniformsLight(GLuint shaderId);
		void setUniformsLight();
		glm::mat4 get_mat();
		GLint width, hight;
		GLfloat fovy, near_plane, far_plane, left, right_fur, bottom, top, pitch, yaw;
		glm::vec3 position, up, target;
		DirLight light;
		GLuint dirLightColor;
        GLuint dirLightIntensity;
        GLuint dirLightDirection;
        GLuint dirLightDiffuseIntensity;
        GLuint EyeWorldPos;
        GLuint MatSpecularIntensityLoc;
        GLuint SpecularPowerLoc;
        GLuint numPointLightsLocation;
        GLuint howCellLoc;
        int howCell;
        GLuint isProcedureLoc;
        int isProcedure;

        struct {
            GLuint color;
            GLuint ambientIntensity;
            GLuint diffuseIntensity;
            GLuint position;
            struct{
                GLuint constant;
                GLuint linear;
                GLuint exp;
            } Atten;
        } pointLightsLocation[MAX_POINT_LIGHTS];
};
