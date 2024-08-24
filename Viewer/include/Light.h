#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad\glad.h>
#include "MeshModel.h"

class Light
{
public:
	Light(glm::vec3 p, int type);
	void Set_A_Color(glm::vec3 color);
	void Set_D_Color(glm::vec3 color);
	void Set_S_Color(glm::vec3 color);
	void Set_Dir(glm::vec3 direction);
	void Set_Pos(glm::vec3 position);
	void Set_Type(int type);

	const glm::vec3 Get_Pos() const;
	const int Get_Type() const;
	void Set_Transform_world_mat(glm::mat4x4& transformation);
	void Set_Rotate_world_mat(glm::mat4x4& transformation, int flag);
	void Set_Transform_model_mat(glm::mat4x4& transformation);
	void Set_Rotate_model_mat(glm::mat4x4& transformation, int flag);
	void Set_trans_matrix();
	const glm::mat4x4 Get_trans_matrix() const;
	const float Get_alpha() const;
	void Set_alpha(float a);
	glm::vec3 Get_A_Color() const;
	glm::vec3 Get_D_Color() const;
	glm::vec3 Get_S_Color() const;
	glm::vec3 Get_parallel() const;
	glm::vec3 Get_Dir() const;



private:
	glm::mat4x4 Transform_model = glm::mat4(1.0f);
	glm::mat4x4 Transform_world = glm::mat4(1.0f);
	glm::mat4x4 Rotate_world = glm::mat4(1.0f);
	glm::mat4x4 Rwx = glm::mat4(1.0f);
	glm::mat4x4 Rwy = glm::mat4(1.0f);
	glm::mat4x4 Rwz = glm::mat4(1.0f);
	glm::mat4x4 Rotate_model = glm::mat4(1.0f);
	glm::mat4x4 Rmx = glm::mat4(1.0f);
	glm::mat4x4 Rmy = glm::mat4(1.0f);
	glm::mat4x4 Rmz = glm::mat4(1.0f);
	glm::mat4x4 transmatrix = glm::mat4(1.0f);
	glm::vec3 A_Color;
	glm::vec3 D_Color;
	glm::vec3 S_Color;
	glm::vec3 Direction;
	glm::vec3 Position = glm::vec3(0, 0, 0);
	glm::vec3 parallel = glm::vec3(0.5, 0.1, 0);
	int Type = 1;
	float alpha;

};