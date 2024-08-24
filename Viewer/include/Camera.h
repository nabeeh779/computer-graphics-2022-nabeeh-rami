#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();
	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	const glm::mat4x4 get_view_mat() const;
	void SetStraightFlag(int flag_);
	int get_straight_flag()const;
	const glm::mat4x4& GetProjectionTransformation() const;
	const glm::mat4x4& GetViewTransformation() const;
	const glm::mat4x4 get_invTransform_Mat() const;
	void set_translation_w(float x, float y, float z);
	void set_rotation_w(float a, float x, float y, float z);
	void set_translation_L(float x, float y, float z);
	void set_rotation_L(float a, float x, float y, float z);
	void set_invTransform_Mat(int flag);
	void set_orth(float x);
	void set_perspective(float x);
	void set_orth_flag(int flag);
	int get_orth_flag()const;
	void set_draw_color(int flag);
	int get_draw_flag();

	glm::vec3 get_eye()const;

private:
	glm::mat4x4 invTransform_Mat = glm::mat4x4(1.0f);
	glm::mat4x4 lookAt_mat_view = glm::mat4x4(1.0f);
	glm::vec3 eye1;
	glm::mat4x4 view_transformation;
	glm::mat4x4 projection_trans = glm::mat4x4(1.0f);
	int straight_flag = 1;


	float w = 1920;
	float h = 1080;
	float aspectrat = w / h;
	float fovy = 45;
	float ortho_val = 0.5;
	float left = (-w) / 2, right = w / 2;
	float  bottom = (-h) / 2, top = h / 2;
	float pro_near = 0.1;
	float pro_far = 200;
	int orth_flag = 1;

	glm::mat4x4 translation_Mat_W = glm::mat4x4(1.0f);
	glm::mat4x4 rotation_Mat_W = glm::mat4x4(1.0f);
	glm::mat4x4 translation_Mat_L = glm::mat4x4(1.0f);
	glm::mat4x4 rotation_Mat_L = glm::mat4x4(1.0f);
	glm::mat4x4 world_x_rotation = glm::mat4x4(1.0f);
	glm::mat4x4 world_y_rotation = glm::mat4x4(1.0f);
	glm::mat4x4 world_z_rotation = glm::mat4x4(1.0f);
	glm::mat4x4 local_X_rotation = glm::mat4x4(1.0f);
	glm::mat4x4 local_Y_rotation = glm::mat4x4(1.0f);
	glm::mat4x4 local_Z_rotation = glm::mat4x4(1.0f);

	int draw_flag = 0;
};