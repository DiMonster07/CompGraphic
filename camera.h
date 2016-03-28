#pragma once
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>

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
		void set_light_param(glm::vec3 color, float ambient_intensity, glm::vec3 direction, float diffuse_intensity);
		void lightRender();
		glm::mat4 get_mat();
		GLint width, hight;
		GLfloat fovy, near_plane, far_plane, left, right_fur, bottom, top, pitch, yaw;
		glm::vec3 position, up, target;
		DirLight light;
};
