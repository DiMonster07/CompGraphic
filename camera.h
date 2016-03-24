#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
	public:
		Camera(float fovy, int width, int hight, float near_plane, float far_plane);
		void move(const glm::vec4 &vec);
		void rotate(float angle, const glm::vec4 &vec);
		void zoom(float value);
		void look_at(const glm::vec4 &Pos, const glm::vec4 &Tar, const glm::vec4 &Up);
		void set_normal_zoom();
		void key_press(bool is_key_press[128]);
		glm::mat4 get_mat();
		glm::vec4 get_dir();
		glm::vec4 get_right();
		glm::vec4 get_pos();
		int width, hight;
		float normal_fovy, fovy, near_plane, far_plane, left, right_fur, bottom, top;
		bool perspective;
		glm::vec4 pos, up, dir, tar, right;
};
