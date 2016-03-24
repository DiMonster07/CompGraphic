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


class Camera
{
	public:
		Camera(GLfloat fovy, GLint width, GLint hight, GLfloat near_plane, GLfloat far_plane);
		void setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up);
		void zoom(float value);
		void rotate();
		void key_callback(bool is_key_press[128]);
		glm::mat4 get_mat();
		GLint width, hight;
		GLfloat fovy, near_plane, far_plane, left, right_fur, bottom, top, pitch, yaw;
		glm::vec3 position, up, target;
};
