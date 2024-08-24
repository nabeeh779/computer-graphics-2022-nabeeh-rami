#include "light.h"

#include <iostream>
#include <fstream>
#include <sstream>

Light::Light(glm::vec3 p, int type)
{
	A_Color = glm::vec3(0.5, 0.5, 0.5);
	D_Color = glm::vec3(0.5, 0.5, 0.5);
	S_Color = glm::vec3(0.5, 0.5, 0.5);
	Direction = glm::vec3(0, 0, -1);
	Position = p;
	Type = type;

}

const float Light::Get_alpha() const
{
	return alpha;
}

void Light::Set_alpha(float a)
{
	alpha = a;
}

void  Light::Set_A_Color(glm::vec3 color)
{
	this->A_Color = color;
}


void  Light::Set_D_Color(glm::vec3 color)
{
	this->D_Color = color;
}


void  Light::Set_S_Color(glm::vec3 color)
{
	this->S_Color = color;
}


void Light::Set_Dir(glm::vec3 direction)
{
	this->Direction = direction;
}

void Light::Set_Pos(glm::vec3 position)
{
	this->Position = position;
}

void Light::Set_Type(int type)
{
	this->Type = type;
}


glm::vec3 Light::Get_A_Color() const
{
	return this->A_Color;
}


glm::vec3 Light::Get_D_Color() const
{
	return this->D_Color;
}

glm::vec3 Light::Get_S_Color() const
{
	return this->S_Color;
}
glm::vec3 Light::Get_Dir() const
{
	return this->Direction;
}

const glm::vec3 Light::Get_Pos() const
{
	return this->Position;
}

const int Light::Get_Type() const
{
	return this->Type;
}

void Light::Set_Transform_world_mat(glm::mat4x4& transformation)
{
	Transform_world = transformation;
}


void Light::Set_Rotate_world_mat(glm::mat4x4& transformation, int f)
{
	if (f == 0) { Rwx = transformation; }
	if (f == 1) { Rwy = transformation; }
	if (f == 2) { Rwz = transformation; }
	Rotate_world = Rwz * Rwy * Rwx;

}
void Light::Set_Transform_model_mat(glm::mat4x4& transformation)
{
	Transform_model = transformation;
}



void Light::Set_Rotate_model_mat(glm::mat4x4& transformation, int f)
{
	if (f == 0) { Rmx = transformation; }
	if (f == 1) { Rmy = transformation; }
	if (f == 2) { Rmz = transformation; }
	Rotate_model = Rmx * Rmz * Rmy;

}

void Light::Set_trans_matrix()
{
	this->transmatrix = Rotate_world * Transform_world * Rotate_model * Transform_model;
}

const glm::mat4x4 Light::Get_trans_matrix() const
{

	return this->transmatrix;

}


glm::vec3 Light::Get_parallel() const
{
	return parallel;
}
