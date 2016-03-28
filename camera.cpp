#include "camera.h"
#include <iostream>
#include <fstream>

using namespace std;

Camera::Camera(GLfloat fovy, GLint width, GLint hight, GLfloat near_plane, GLfloat far_plane) :
        fovy(fovy), width(width), hight(hight), near_plane(near_plane), far_plane(far_plane)
{
    this->yaw = 90.0f;
    this->pitch = 0.0f;
};

void Camera::setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
    this->position = position;
    this->target = target;
    this->up = up;
}

void Camera::zoom(float value)
{
	fovy += value;
	if (fovy <= 10) { fovy = 10; }
	else if (fovy >= 150) { fovy = 150; }
}

void Camera::rotate()
{
    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    if (this->pitch < -89.0f)
        this->pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->target = glm::normalize(front);
}

void Camera::set_light_param(glm::vec3 color, float ambient_intensity, glm::vec3 direction, float diffuse_intensity)
{
    this->light.color = color;
    this->light.ambient_intensity = ambient_intensity;
    this->light.direction = direction;
    this->light.diffuse_intensity = diffuse_intensity;
}

void Camera::key_callback(bool is_key_press[128])
{
    GLfloat rotateSpeed = 5.0f;
    GLfloat cameraSpeed = 1.0f;
    GLfloat zoomSpeed = 5.0f;
    for (int i = 0; i < 128; i++)
    {
        if (is_key_press[i])
		{
			switch (i)
			{
				case KEY_W:
					this->position += cameraSpeed * this->target;
					break;
				case KEY_S:
					this->position -= cameraSpeed * this->target;
					break;
				case KEY_D:
					this->position += glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;
					break;
				case KEY_A:
					this->position -= glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;
					break;
				case KEY_J:
				    this->pitch -= rotateSpeed;
					this->rotate();
					break;
				case KEY_H:
				    this->yaw -= rotateSpeed;
					this->rotate();
					break;
				case KEY_U:
				    this->pitch += rotateSpeed;
					this->rotate();
					break;
				case KEY_K:
				    this->yaw += rotateSpeed;
					this->rotate();
					break;
                case KEY_Q:
					this->zoom(-zoomSpeed);
					break;
                case KEY_E:
					this->zoom(zoomSpeed);
					break;
                case KEY_Z:
					this->light.ambient_intensity -= 0.05f;
					break;
                case KEY_X:
					this->light.ambient_intensity += 0.05f;
					break;
                case KEY_C:
					this->light.diffuse_intensity -= 0.05f;
					break;
                case KEY_V:
					this->light.diffuse_intensity += 0.05f;
					break;
				case 27:
					exit(0);
					break;
			}
		}
    }
}

glm::mat4 Camera::get_mat()
{
    glm::mat4 view = glm::lookAt(this->position, this->position + this->target, this->up);
	glm::mat4 projection = glm::perspective(this->fovy, (GLfloat)this->width / (GLfloat)this->hight, this->near_plane, this->far_plane);
	return projection * view;
}
