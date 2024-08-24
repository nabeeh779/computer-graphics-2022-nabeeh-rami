#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <memory>
#include "Texture2D.h"



class Renderer
{
public:
	Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void Render( Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	void PutPixel(const int i, const int j, const glm::vec3& color);
	void DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color);	int view_width;
	int view_hight;
	void CreateBuffers(int w, int h);
	void Set_ZBuffer();
	void CreateOpenglBuffer();
	void Set_Z_value(int i, int j, float z);
	float Get_Z_value(int i, int j);
	void Scan_and_set(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
	void InitOpenglRendering();
	bool IsInside(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3);
	glm::vec3 Calc_z(int x, int y, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& val1, const glm::vec3& val2, const glm::vec3& val3);
	void DrawTriangles();
	void DrawLights(const Scene& scene, glm::mat4x4& inverse, glm::mat4x4& lookat, glm::mat4x4& projection, glm::mat4x4& st_view);
	glm::vec3 Ambient_color(glm::vec3& light, glm::vec3& model);
	glm::vec3 Diffuse_Color(glm::vec3 n, glm::vec3& i, glm::vec3& color, Light& light);
	glm::vec3 Specular_Color(glm::vec3& n, glm::vec3& i, glm::vec3& v, glm::vec3& color, Light& light);
	void filltheTriangle_gouraud(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, glm::vec3& c1, glm::vec3& c2, glm::vec3& c3);
	void filltheTriangle_phong(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, glm::vec3 n1, glm::vec3 n2, glm::vec3 n3, const Scene& scene, Light& light, glm::vec3 position, int flag);
	void filltheTriangle_Flat(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, glm::vec3 color);
	void LoadShaders();
	void LoadTextures();
	Texture2D texture1;

	void RandomColor(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);


	float* color_buffer;
	float* Z_buffer_t;
	float maxZ = std::numeric_limits<float>::min(); //
	float minZ = std::numeric_limits<float>::max();; //
	GLuint gl_screen_tex;
	GLuint gl_screen_vtc;
	ShaderProgram lightShader;
	ShaderProgram colorShader;
};