#include "camera.h"

Camera::Camera(float fovy, int width, int hight, float near_plane, float far_plane) :
        fovy(fovy), width(width), hight(hight), near_plane(near_plane), far_plane(far_plane)
{
	normal_fovy = fovy;
	perspective = true;
}

void Camera::move(const glm::vec4 &vec)
{
	pos = pos + vec;
}

void Camera::rotate(float angle, const glm::vec4 &vec)
{

}

void Camera::zoom(float value)
{
	fovy += value;
	if (fovy <= 10)
	{
		fovy = 10;
	}
	else if (fovy >= 150)
	{
		fovy = 150;
	}
}

void Camera::look_at(const glm::vec4 &Position, const glm::vec4 &Target, const glm::vec4 &Up)
{
    
}

void Camera::set_normal_zoom()
{
	fovy = normal_fovy;
}

void Camera::key_press(bool is_key_press[128])
{

}

glm::mat4 Camera::get_mat()
{
	glm::mat4 projection, view;
	projection = glm::perspective(fovy, (float)((float)width / (float)hight), near_plane, far_plane);
	view = glm::mat4(right[0], right[1], right[2], 0, up[0], up[1], up[2], 0, dir[0], dir[1], dir[2], 0, 0, 0, 0, 1)
			    * glm::mat4(1, 0, 0, -pos[0], 0, 1, 0, -pos[1], 0, 0, 1, -pos[2], 0, 0, 0, 1);
	return projection * view;
}

glm::vec4 Camera::get_dir()
{
	return dir;
}

glm::vec4 Camera::get_right()
{
	return right;
}

glm::vec4 Camera::get_pos()
{
	return pos;
}
