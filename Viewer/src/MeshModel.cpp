#include "MeshModel.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <random>

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords, const std::string& modelName, glm::mat4x4 T, float MAX, float maxX, float maxY, float maxZ, float minX, float minY, float minZ) :
	faces(faces),
	vertices(vertices),
	normals(normals),
	model_name(model_name),
	Mmat(T),
	textureCoords(textureCoords),
	translation_Mat_W(glm::mat4x4(1.0f)),
	rotation_Mat_W(glm::mat4x4(1.0f)),
	scaling_Mat_W(glm::mat4x4(1.0f)),
	translation_Mat_L(glm::mat4x4(1.0f)),
	rotation_Mat_L(glm::mat4x4(1.0f)),
	scaling_Mat_L(glm::mat4x4(1.0f)),
	R_X_L(glm::mat4x4(1.0f)),
	R_Y_L(glm::mat4x4(1.0f)),
	R_Z_L(glm::mat4x4(1.0f)),
	Transform_Mat(glm::mat4x4(1.0f)),
	R_X_W(glm::mat4x4(1.0f)),
	R_Y_W(glm::mat4x4(1.0f)),
	R_Z_W(glm::mat4x4(1.0f)),
	min_x(minX),
	min_y(minY),
	min_z(minZ),
	max_x(maxX),
	max_y(maxY),
	max_z(maxZ)

{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, 1);
	color = glm::vec3(dist(mt), dist(mt), dist(mt));
	center = glm::vec3((maxX + minX) / 2, (maxY + minY) / 2, (minZ + maxZ) / 2);
	modelVertices.reserve(3 * faces.size());
	for (int i = 0; i < faces.size(); i++)
	{
		Face currentFace = faces.at(i);
		for (int j = 0; j < 3; j++)
		{
			int vertexIndex = currentFace.GetVertexIndex(j) - 1;
			int normalIndex = currentFace.GetNormalIndex(j) - 1;

			Vertex vertex;
			vertex.position = vertices[vertexIndex];
			if (normals.size())
				vertex.normal = normals[normalIndex];

			if (textureCoords.size() > 0)
			{
				int textureCoordsIndex = currentFace.GetTextureIndex(j) - 1;
				vertex.textureCoords = textureCoords[textureCoordsIndex];
			}

			modelVertices.push_back(vertex);
		}
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, modelVertices.size() * sizeof(Vertex), &modelVertices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Vertex Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// unbind to make sure other code does not change it somewhere else
	glBindVertexArray(0);
}

MeshModel::~MeshModel()
{
}

const Face& MeshModel::GetFace(int index) const
{
	return faces[index];
}

int MeshModel::GetFacesCount() const
{
	return faces.size();
}

const std::string& MeshModel::GetModelName() const
{
	return model_name;
}

const glm::mat4x4 MeshModel::GetM() const
{
	return Mmat;
}

void MeshModel::set_Transform_Mat(int flag)
{
	if (flag == 0)
	{
		Transform_Mat = scaling_Mat_W * R_Z_W * R_Y_W * R_X_W * translation_Mat_W * scaling_Mat_L * R_Z_L * R_Y_L * R_X_L * translation_Mat_L;
	}
	else {
		Transform_Mat = glm::mat4x4(1.0f);
		translation_Mat_W = glm::mat4x4(1.0f);
		rotation_Mat_W = glm::mat4x4(1.0f);
		scaling_Mat_W = glm::mat4x4(1.0f);
		translation_Mat_L = glm::mat4x4(1.0f);
		rotation_Mat_L = glm::mat4x4(1.0f);
		scaling_Mat_L = glm::mat4x4(1.0f);
		R_X_W = glm::mat4x4(1.0f);
		R_Y_W = glm::mat4x4(1.0f);
		R_Z_W = glm::mat4x4(1.0f);
		R_X_L = glm::mat4x4(1.0f);
		R_Y_L = glm::mat4x4(1.0f);
		R_Z_L = glm::mat4x4(1.0f);
	}
}

const glm::mat4x4 MeshModel::get_Transform_Mat() const
{
	return Transform_Mat;
}

const glm::vec3 MeshModel::GetVer(int index) const
{
	return vertices[index - 1];
}

glm::vec4 MeshModel::get_Up_vec1() const
{
	glm::mat4x4 mymat;
	return (Transform_Mat * glm::vec4(max_x, max_y, max_z, 1));
}

void MeshModel::set_translation_w(float x, float y, float z)
{
	translation_Mat_W = glm::translate(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

glm::vec4 MeshModel::get_Up_vec2() const
{
	glm::mat4x4 mymat;
	return (Transform_Mat * glm::vec4(max_x, max_y, min_z, 1));
}

void MeshModel::set_rotation_w(float a, float x, float y, float z)
{
	rotation_Mat_W = glm::rotate(a, glm::vec3(x, y, z));
	if (x == 1) {
		R_X_W = rotation_Mat_W;
	}
	if (y == 1) {
		R_Y_W = rotation_Mat_W;
	}
	if (z == 1) {
		R_Z_W = rotation_Mat_W;
	}
	set_Transform_Mat(0);
}

glm::vec4 MeshModel::get_Up_vec3() const
{
	glm::mat4x4 mymat;
	return (Transform_Mat * glm::vec4(min_x, max_y, max_z, 1));
}

void MeshModel::set_scaling_w(float x, float y, float z)
{
	scaling_Mat_W = glm::scale(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

glm::vec4 MeshModel::get_Up_vec4() const
{
	glm::mat4x4 mymat;
	return (Transform_Mat * glm::vec4(min_x, max_y, min_z, 1));
}

void MeshModel::set_translation_L(float x, float y, float z)
{
	translation_Mat_L = glm::translate(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

void MeshModel::set_rotation_L(float a, float x, float y, float z)
{
	rotation_Mat_L = glm::rotate(a, glm::vec3(x, y, z));
	if (x == 1) {
		R_X_L = rotation_Mat_L;
	}
	if (y == 1) {
		R_Y_L = rotation_Mat_L;
	}
	if (z == 1) {
		R_Z_L = rotation_Mat_L;
	}
	set_Transform_Mat(0);
}

void MeshModel::set_scaling_L(float x, float y, float z)
{
	scaling_Mat_L = glm::scale(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

void MeshModel::set_show_box_flag(int f)
{
	show_box_flag = f;
}

void MeshModel::set_facenorm_flag(int f)
{
	faceNorm_flag = f;
}

int MeshModel::get_facenorm_flag()
{
	return faceNorm_flag;
}

glm::vec4 MeshModel::get_Down_vec1() const
{
	glm::mat4x4 mymat;

	return (Transform_Mat * glm::vec4(max_x, min_y, max_z, 1));
}

const glm::mat4x4 MeshModel::Get_rotation_W() const
{
	return rotation_Mat_W;
}

int MeshModel::get_show_box_flag()
{
	return show_box_flag;;
}

glm::vec4 MeshModel::get_Down_vec2() const
{
	glm::mat4x4 mymat;
	return (Transform_Mat * glm::vec4(max_x, min_y, min_z, 1));
}

const glm::mat4x4 MeshModel::Get_rotation_L() const
{
	return rotation_Mat_L;
}

glm::vec4 MeshModel::get_Down_vec3() const
{
	glm::mat4x4 mymat;

	return (Transform_Mat * glm::vec4(min_x, min_y, max_z, 1));
}

void MeshModel::set_vernorm_flag(int f)
{
	verNorm_flag = f;
}

glm::vec4 MeshModel::get_Down_vec4() const
{
	glm::mat4x4 mymat;

	return (Transform_Mat * glm::vec4(min_x, min_y, min_z, 1));
}

int MeshModel::get_vernorm_flag()
{
	return verNorm_flag;;
}

void MeshModel::print_vers()
{
	std::cout << "all the  vertices:";
	for (int i = 1; i < vertices.size(); i++)
	{
		std::cout << '[' << vertices[i - 1].x << ',' << vertices[i - 1].y << ',' << vertices[i - 1].z << ']';
		std::cout << "\n";

	}
}

void MeshModel::print_faces(float x, float y, float z)
{
	translation_Mat_W = glm::translate(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

const glm::vec3 MeshModel::GetNorms(int index) const
{
	return normals[index - 1];
}

float MeshModel::Get_orthoGraphicVal()
{
	float ortho_val = 0;
	if (model_name == "banana.obj")
	{
		ortho_val = 0.5f;
	}
	if (model_name == "Sphere.obj")
	{
		ortho_val = 0.5f;
	}
	if (model_name == "beethoven.obj")
	{
		ortho_val = 25.0f;
	}
	if (model_name == "bishop.obj")
	{
		ortho_val = 1.5f;
	}
	if (model_name == "bunny.obj")
	{
		ortho_val = 5.0f;
	}
	if (model_name == "camera.obj")
	{
		ortho_val = 30.0f;
	}
	if (model_name == "chain.obj")
	{
		ortho_val = 15.0f;
	}
	if (model_name == "cow.obj")
	{
		ortho_val = 20.0f;
	}
	if (model_name == "demo.obj")
	{
		ortho_val = 20.0f;
	}
	if (model_name == "dolphin.obj")
	{
		ortho_val = 800.0f;
	}
	if (model_name == "pawn.obj")
	{
		ortho_val = 0.3f;
	}
	if (model_name == "teapot.obj")
	{
		ortho_val = 15.0f;
	}
	if (model_name == "cheburashka.obj")
	{
		ortho_val = 100.0f;
	}
	if (model_name == "beetle.obj")
	{
		ortho_val = 5.0f;
	}
	if (model_name == "feline.obj")
	{
		ortho_val = 10.0f;
	}
	return ortho_val;
}




void MeshModel::Set_colorbutton(int c)
{
	this->colors_var = c;
}
int MeshModel::Get_colorbutton() const
{
	return colors_var;
}


void MeshModel::Set_modelAmbient_Color(glm::vec3 color)
{
	Ambient_Color = color;
}
void MeshModel::Set_modelDiffuse_Color(glm::vec3 color)
{
	Diffuse_Color = color;
}
void MeshModel::Set_modelSpecular_Color(glm::vec3 color)
{
	Specular_Color = color;
}
glm::vec3 MeshModel::Get_modelAmbient_Color() const
{
	return Ambient_Color;
}
glm::vec3 MeshModel::Get_modelDiffuse_Color() const
{
	return Diffuse_Color;
}
glm::vec3 MeshModel::Get_modelSpecular_Color() const
{
	return Specular_Color;
}


GLuint MeshModel::GetVAO() const
{
	return vao;
}

const std::vector<Vertex>& MeshModel::GetModelVertices()
{
	return modelVertices;
}