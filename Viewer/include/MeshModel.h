#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Face.h"
#include <glad/glad.h>
#include <memory>
#include "MeshModel.h"


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};

class MeshModel
{
public:
	MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords, const std::string& modelName, glm::mat4x4 T, float MAX, float maxX, float maxY, float maxZ, float minX, float minY, float minZ);
	virtual ~MeshModel();
	const Face& GetFace(int index) const;
	int GetFacesCount() const;
	const std::string& GetModelName() const;
	const glm::mat4x4 MeshModel::GetM() const;
	void set_Transform_Mat(int flag);
	const glm::mat4x4 get_Transform_Mat() const;
	const glm::vec3 GetVer(int index) const;
	glm::vec4 get_Up_vec1() const;
	glm::vec4 get_Up_vec2() const;
	glm::vec4 get_Up_vec3() const;
	glm::vec4 get_Up_vec4() const;
	void set_translation_w(float x, float y, float z);
	void set_rotation_w(float a, float x, float y, float z);
	void set_scaling_w(float x, float y, float z);
	void set_translation_L(float x, float y, float z);
	void set_rotation_L(float a, float x, float y, float z);
	void set_scaling_L(float x, float y, float z);
	const glm::mat4x4 Get_rotation_W() const;
	const glm::mat4x4 Get_rotation_L() const;
	glm::vec4 get_Down_vec1() const;
	glm::vec4 get_Down_vec2() const;
	glm::vec4 get_Down_vec3() const;
	glm::vec4 get_Down_vec4() const;
	int get_facenorm_flag();
	void set_facenorm_flag(int f);
	int get_show_box_flag();
	int get_vernorm_flag();
	float Get_orthoGraphicVal();
	void set_show_box_flag(int f);
	const glm::vec3 GetNorms(int index) const;
	void set_vernorm_flag(int f);
	void Set_colorbutton(int c);
	int Get_colorbutton() const;
	void print_vers();
	void print_faces(float x, float y, float z);
	void Set_modelAmbient_Color(glm::vec3 color);
	glm::vec3 Get_modelAmbient_Color() const;
	void Set_modelDiffuse_Color(glm::vec3 color);
	glm::vec3 Get_modelDiffuse_Color() const;
	void Set_modelSpecular_Color(glm::vec3 color);
	glm::vec3 Get_modelSpecular_Color() const;
	glm::vec3 center;


	const std::vector<Vertex>& GetModelVertices();
	GLuint GetVAO() const;
	std::vector<glm::vec2> textureCoords;


protected:
	std::vector<Vertex> modelVertices;
	GLuint vbo;
	GLuint vao;


private:
	std::vector<Face> faces;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::string model_name;
	glm::mat4x4 scaling_Mat_L;
	glm::mat4x4 Mmat;
	glm::mat4x4 translation_Mat_W;
	glm::mat4x4 rotation_Mat_W;
	glm::mat4x4 scaling_Mat_W;
	glm::mat4x4 translation_Mat_L;
	glm::mat4x4 rotation_Mat_L;
	glm::mat4x4 Transform_Mat;
	glm::mat4x4 R_X_W;
	glm::mat4x4 R_Y_W;
	glm::mat4x4 R_Z_W;
	glm::mat4x4 R_X_L;
	glm::mat4x4 R_Y_L;
	glm::mat4x4 R_Z_L;
	float max_x;
	float max_y;
	float max_z;
	float min_x;
	float min_y;
	float min_z;
	int show_box_flag;
	int verNorm_flag;
	int faceNorm_flag;
	int colors_var = 0;

	float maxX = 0, minX = 0, maxY = 0, minY = 0, maxZ = 0, minZ = 0, MAX = 0;
	glm::vec3 Ambient_Color;
	glm::vec3 Diffuse_Color;
	glm::vec3 Specular_Color;
	glm::vec3 color;
};
