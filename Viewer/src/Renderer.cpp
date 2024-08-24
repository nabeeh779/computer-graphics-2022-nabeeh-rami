#define _USE_MATH_DEFINES
#include "MeshModel.h"

#include <cmath>
#include <algorithm>
#include <iostream>

#include "Renderer.h"
#include "MeshModel.h"
#include "InitShader.h"


#include <glad/glad.h>

#include <imgui/imgui.h>
#include <vector>
#include <memory>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))

Renderer::Renderer(int viewport_width, int viewport_height) :
	view_width(viewport_width),
	view_hight(viewport_height)
{
	
	CreateBuffers(viewport_width, viewport_height);

}

Renderer::~Renderer()
{
	delete[] color_buffer;
	delete[] Z_buffer_t;
}

void Renderer::PutPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= view_width) return;
	if (j < 0) return; if (j >= view_hight) return;

	color_buffer[INDEX(view_width, i, j, 0)] = color.x;
	color_buffer[INDEX(view_width, i, j, 1)] = color.y;
	color_buffer[INDEX(view_width, i, j, 2)] = color.z;
}

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{


	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	if (abs(dy) < abs(dx))
	{
		if (p1.x < p2.x)
		{
			int x1 = p1.x;
			int y1 = p1.y;
			int yi = 1;
			int e = -dx;
			if (dy < 0)
			{
				yi = -1;
				dy = -dy;
			}
			while (x1 <= p2.x)
			{
				if (e > 0)
				{
					y1 += yi;
					e -= 2 * dx;
				}
				PutPixel(x1, y1, color);
				x1 += 1;
				e += 2 * dy;

			}
		}
		else if (p1.x > p2.x)
		{
			int x2 = p2.x;
			int y2 = p2.y;
			int yi = 1;
			int e;
			dx = p1.x - p2.x;
			dy = p1.y - p2.y;
			e = -dx;

			if (dy < 0)
			{
				yi = -1;
				dy = -dy;
			}
			while (x2 <= p1.x)
			{
				if (e > 0)
				{
					y2 += yi;
					e -= 2 * dx;
				}
				PutPixel(x2, y2, color);
				x2 += 1;
				e += 2 * dy;

			}

		}
	}
	else
	{
		if (p1.y < p2.y)
		{

			int x1 = p1.x;
			int y1 = p1.y;
			int xi = 1;
			int e;
			dx = p2.x - p1.x;
			dy = p2.y - p1.y;
			e = -dy;

			if (dx < 0)
			{
				xi = -1;
				dx = -dx;
			}
			while (y1 <= p2.y)
			{
				if (e > 0)
				{
					x1 += xi;
					e -= 2 * dy;
				}
				PutPixel(x1, y1, color);
				y1 += 1;
				e += 2 * dx;

			}


		}
		else if (p1.y > p2.y)
		{
			int x2 = p2.x;
			int y2 = p2.y;
			int xi = 1;
			int e;
			dx = p1.x - p2.x;
			dy = p1.y - p2.y;
			e = -dy;

			if (dx < 0)
			{
				xi = -1;
				dx = -dx;
			}
			while (y2 <= p1.y)
			{
				if (e > 0)
				{
					x2 += xi;
					e -= 2 * dy;
				}
				PutPixel(x2, y2, color);
				y2 += 1;
				e += 2 * dx;

			}
		}

	}

}

void Renderer::CreateBuffers(int w, int h)
{
	CreateOpenglBuffer(); //Do not remove this line.
	color_buffer = new float[3 * w * h];
	ClearColorBuffer(glm::vec3(0.0f, 0.0f, 0.0f));
	Z_buffer_t = new float[w * h];
	Set_ZBuffer();
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::InitOpenglRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &gl_screen_tex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &gl_screen_vtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(gl_screen_vtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[] = {
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[] = {
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1 };

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc) + sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(vtc));

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"), 0);
}

void Renderer::CreateOpenglBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, view_width, view_hight, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, view_width, view_hight);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, view_width, view_hight, GL_RGB, GL_FLOAT, color_buffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(gl_screen_vtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < view_width; i++)
	{
		for (int j = 0; j < view_hight; j++)
		{
			PutPixel(i, j, color);
		}
	}
}
int Renderer::GetViewportWidth() const
{
	return view_width;
}

int Renderer::GetViewportHeight() const
{
	return view_hight;
}

void Renderer::filltheTriangle_Flat(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, glm::vec3 color)
{
	float minY = std::min(std::min(p1.y, p2.y), p3.y);
	float maxY = std::max(std::max(p1.y, p2.y), p3.y);
	float minX = std::min(std::min(p1.x, p2.x), p3.x);
	float maxX = std::max(std::max(p1.x, p2.x), p3.x);
	for (int j = maxY; j >= minY; j--)
	{
		for (int i = minX; i <= maxX; i++)
		{
			if (IsInside(i, j, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y))
			{
				glm::vec3 z = Calc_z(i, j, p1, p2, p3, p1, p2, p3);
				if (z.z <= Get_Z_value(i, j))
				{
					if (i < 0) return; if (i >= view_width) return;
					if (j < 0) return; if (j >= view_hight) return;

					color_buffer[INDEX(view_width, i, j, 0)] += color.x;
					color_buffer[INDEX(view_width, i, j, 1)] += color.y;
					color_buffer[INDEX(view_width, i, j, 2)] += color.z;


					if (color_buffer[INDEX(view_width, i, j, 0)] > 1.f) //
						color_buffer[INDEX(view_width, i, j, 0)] = 1.f;

					if (color_buffer[INDEX(view_width, i, j, 1)] > 1.f)
						color_buffer[INDEX(view_width, i, j, 1)] = 1.f;

					if (color_buffer[INDEX(view_width, i, j, 2)] > 1.f)
						color_buffer[INDEX(view_width, i, j, 2)] = 1.f;


				}

			}
		}

	}
}

void Renderer::filltheTriangle_phong(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, glm::vec3 n1, glm::vec3 n2, glm::vec3 n3, const Scene& scene, Light& light, glm::vec3 position, int flag)
{
	float minY = std::min(std::min(p1.y, p2.y), p3.y);
	float maxY = std::max(std::max(p1.y, p2.y), p3.y);
	float minX = std::min(std::min(p1.x, p2.x), p3.x);
	float maxX = std::max(std::max(p1.x, p2.x), p3.x);
	glm::vec3 I;
	for (int j = maxY; j >= minY; j--)
	{
		for (int i = minX; i <= maxX; i++)
		{
			if (IsInside(i, j, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y))
			{
				glm::vec3 z = Calc_z(i, j, p1, p2, p3, p1, p2, p3);
				if (z.z <= Get_Z_value(i, j))
				{
					if (i < 0) return; if (i >= view_width) return;
					if (j < 0) return; if (j >= view_hight) return;
					if (flag == 2) //point
					{
						I = normalize(z - position);
					}
					else
					{
						I = normalize(light.Get_Dir());
					}
					glm::vec3 n = Calc_z(i, j, p1, p2, p3, n1, n2, n3);
					glm::vec3 c = Ambient_color(light.Get_A_Color(), scene.GetActiveModel()->Get_modelAmbient_Color());
					c += Diffuse_Color(n, I, scene.GetActiveModel()->Get_modelDiffuse_Color(), light);
					c += Specular_Color(n, I, glm::normalize(scene.GetActiveCamera().get_eye()), scene.GetActiveModel()->Get_modelSpecular_Color(), light);


					color_buffer[INDEX(view_width, i, j, 0)] += c.x;
					color_buffer[INDEX(view_width, i, j, 1)] += c.y;
					color_buffer[INDEX(view_width, i, j, 2)] += c.z;

					if (color_buffer[INDEX(view_width, i, j, 0)] > 1.f) //
						color_buffer[INDEX(view_width, i, j, 0)] = 1.f;

					if (color_buffer[INDEX(view_width, i, j, 1)] > 1.f)
						color_buffer[INDEX(view_width, i, j, 1)] = 1.f;

					if (color_buffer[INDEX(view_width, i, j, 2)] > 1.f)
						color_buffer[INDEX(view_width, i, j, 2)] = 1.f;


				}

			}
		}

	}
}
void Renderer::filltheTriangle_gouraud(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, glm::vec3& c1, glm::vec3& c2, glm::vec3& c3)
{
	float minY = std::min(std::min(p1.y, p2.y), p3.y);
	float maxY = std::max(std::max(p1.y, p2.y), p3.y);
	float minX = std::min(std::min(p1.x, p2.x), p3.x);
	float maxX = std::max(std::max(p1.x, p2.x), p3.x);
	for (int j = maxY; j >= minY; j--)
	{
		for (int i = minX; i <= maxX; i++)
		{
			if (IsInside(i, j, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y))
			{
				glm::vec3 z = Calc_z(i, j, p1, p2, p3, p1, p2, p3);
				if (z.z <= Get_Z_value(i, j))
				{
					if (i < 0) return; if (i >= view_width) return;
					if (j < 0) return; if (j >= view_hight) return;
					glm::vec3 c = Calc_z(i, j, p1, p2, p3, c1, c2, c3);
					color_buffer[INDEX(view_width, i, j, 0)] += c.x;
					color_buffer[INDEX(view_width, i, j, 1)] += c.y;
					color_buffer[INDEX(view_width, i, j, 2)] += c.z;

					if (color_buffer[INDEX(view_width, i, j, 0)] > 1.f) //
						color_buffer[INDEX(view_width, i, j, 0)] = 1.f;

					if (color_buffer[INDEX(view_width, i, j, 1)] > 1.f)
						color_buffer[INDEX(view_width, i, j, 1)] = 1.f;

					if (color_buffer[INDEX(view_width, i, j, 2)] > 1.f)
						color_buffer[INDEX(view_width, i, j, 2)] = 1.f;




				}

			}
		}

	}
}



glm::vec3 Renderer::Ambient_color(glm::vec3& light, glm::vec3& model)
{
	return glm::vec3(light.x * model.x, light.y * model.y, light.z * model.z);
}

glm::vec3 Renderer::Diffuse_Color(glm::vec3 n, glm::vec3& i, glm::vec3& color, Light& light)
{
	glm::vec3 Lcolor = light.Get_D_Color();
	glm::vec3 Color(Lcolor.x * color.x, Lcolor.y * color.y, Lcolor.z * color.z);
	float I_n = glm::dot(-n, i);
	return Color * I_n;
}
glm::vec3 Renderer::Specular_Color(glm::vec3& n, glm::vec3& i, glm::vec3& v, glm::vec3& color, Light& light)
{
	int alpha = light.Get_alpha();
	glm::vec3 Lcolor = light.Get_S_Color();
	glm::vec3 Color(Lcolor.x * color.x, Lcolor.y * color.y, Lcolor.z * color.z);
	glm::vec3 r = (2.f * glm::dot(-n, i) * n - i);
	float t = std::pow(std::max(0.f, glm::dot(r, v)), alpha); //
	return t * Color;
}

void Renderer::Set_ZBuffer()
{
	minZ = FLT_MAX;
	maxZ = FLT_MIN;
	for (int i = 0; i < view_width; i++)
	{
		for (int j = 0; j < view_hight; j++)
		{
			Z_buffer_t[Z_INDEX(view_width, i, j)] = FLT_MAX;

			color_buffer[INDEX(view_width, i, j, 0)] = 0.f;
			color_buffer[INDEX(view_width, i, j, 1)] = 0.f;
			color_buffer[INDEX(view_width, i, j, 2)] = 0.f;
		}
	}
}


void Renderer::Set_Z_value(int i, int j, float z)
{
	if (i < 0) return; if (i >= view_width) return;
	if (j < 0) return; if (j >= view_hight) return;
	this->Z_buffer_t[Z_INDEX(view_width, i, j)] = z;
}

float Renderer::Get_Z_value(int i, int j)
{
	if (i < 0) return 0; if (i >= view_width) return 0;
	if (j < 0) return 0; if (j >= view_hight) return 0;
	return this->Z_buffer_t[Z_INDEX(view_width, i, j)];
}
bool Renderer::IsInside(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
{

	//https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/

	float X = abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);


	float X1 = abs((x * (y2 - y3) + x2 * (y3 - y) + x3 * (y - y2)) / 2.0);

	float X2 = abs((x1 * (y - y3) + x * (y3 - y1) + x3 * (y1 - y)) / 2.0);


	float X3 = abs((x1 * (y2 - y) + x2 * (y - y1) + x * (y1 - y2)) / 2.0);

	if (X == X1 + X2 + X3) return 1;
	return 0;

}

glm::vec3 Renderer::Calc_z(int x, int y, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& val1, const glm::vec3& val2, const glm::vec3& val3)
{
	float X1 = abs((x * (p1.y - p2.y) + p1.x * (p2.y - y) + p2.x * (y - p1.y)) / 2.0);

	float X2 = abs((x * (p1.y - p3.y) + p1.x * (p3.y - y) + p3.x * (y - p1.y)) / 2.0);

	float X3 = abs((x * (p3.y - p2.y) + p3.x * (p2.y - y) + p2.x * (y - p3.y)) / 2.0);
	float X = X1 + X2 + X3;
	glm::vec3 a = (X1 / X) * val3;
	glm::vec3 b = (X2 / X) * val2;
	glm::vec3 g = (X3 / X) * val1;
	return (a + b + g);
}

void Renderer::RandomColor(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
{
	float minY = std::min(std::min(p1.y, p2.y), p3.y);
	float maxY = std::max(std::max(p1.y, p2.y), p3.y);
	float minX = std::min(std::min(p1.x, p2.x), p3.x);
	float maxX = std::max(std::max(p1.x, p2.x), p3.x);
	float temp = 255 * 255;
	glm::vec3 random_color = glm::vec3(static_cast <float>(rand() / temp), static_cast <float>(rand() / temp), static_cast <float>(rand() / temp));
	for (int j = maxY; j >= minY; j--)
	{
		for (int i = minX; i <= maxX; i++)
		{
			if (IsInside(i, j, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y))
			{
				glm::vec3 z = Calc_z(i, j, p1, p2, p3, p1, p2, p3);
				if (z.z <= Get_Z_value(i, j))
				{
					PutPixel(i, j, random_color);
				}

			}
		}
	}
}

void Renderer::Scan_and_set(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
{

	float minY = std::min(std::min(p1.y, p2.y), p3.y);
	float maxY = std::max(std::max(p1.y, p2.y), p3.y);
	float minX = std::min(std::min(p1.x, p2.x), p3.x);
	float maxX = std::max(std::max(p1.x, p2.x), p3.x);
	for (int j = maxY; j >= minY; j--)
	{
		for (int i = minX; i <= maxX; i++)
		{
			if (IsInside(i, j, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y))
			{
				glm::vec3 z = Calc_z(i, j, p1, p2, p3, p1, p2, p3);
				if (z.z <= Get_Z_value(i, j))
				{
					maxZ = std::max(maxZ, z.z);
					minZ = std::min(minZ, z.z);
					Set_Z_value(i, j, z.z);

				}

			}
		}

	}

}


void Renderer::DrawTriangles()
{
	glm::vec3 _color;

	for (int i = 0; i < view_width; i++)
	{
		for (int j = 0; j < view_hight; j++)
		{
			float z = Get_Z_value(i, j);
			if (z != FLT_MAX)
			{

				float a = 1 / (maxZ - minZ);
				float b = -1 * a * minZ;
				float c = 1 - (a * z + b);
				_color = glm::vec3(c, c, c);


				PutPixel(i, j, _color);


			}

		}
	}

}


void Renderer::DrawLights(const Scene& scene, glm::mat4x4& inverse, glm::mat4x4& lookat, glm::mat4x4& projection, glm::mat4x4& st_view)
{
	int count = scene.Get_count_ofLights();
	glm::mat4x4 transmat;
	for (int i = 0; i < count; i++)
	{
		int t = scene.GetLight(i)->Get_Type();
		if (t == 2) //point
		{
			transmat = scene.GetLight(i)->Get_trans_matrix();
			glm::vec3 temp = scene.GetLight(i)->Get_Pos();
			glm::vec4 pos = projection * lookat * inverse * transmat * glm::vec4(temp, 1);
			if (!(scene.GetActiveCamera().get_orth_flag()))
			{
				pos /= pos.w;
			}
			pos = st_view * pos;
			glm::vec3 v1_light(pos.x, pos.y + 20, -pos.z);
			glm::vec3 v2_light(pos.x + 20, pos.y - 20, -pos.z);
			glm::vec3 v3_light(pos.x - 20, pos.y - 20, -pos.z);
			float minY = std::min(std::min(v1_light.y, v2_light.y), v3_light.y);
			float maxY = std::max(std::max(v1_light.y, v2_light.y), v3_light.y);
			float minX = std::min(std::min(v1_light.x, v2_light.x), v3_light.x);
			float maxX = std::max(std::max(v1_light.x, v2_light.x), v3_light.x);
			glm::vec3 white_color = glm::vec3(1, 1, 1);
			for (int j = maxY; j >= minY; j--)
			{
				for (int i = minX; i <= maxX; i++)
				{
					if (IsInside(i, j, v1_light.x, v1_light.y, v2_light.x, v2_light.y, v3_light.x, v3_light.y))
					{
						glm::vec3 z = Calc_z(i, j, v1_light, v2_light, v3_light, v1_light, v2_light, v3_light);
						if (z.z <= Get_Z_value(i, j))
						{
							PutPixel(i, j, white_color);
							Set_Z_value(i, j, z.z);
						}
					}
				}
			}
		}
		else
		{
			transmat = scene.GetLight(i)->Get_trans_matrix();
			glm::vec4 p = glm::vec4(scene.GetLight(i)->Get_parallel(), 1);
			glm::vec4 direction = glm::vec4(normalize(scene.GetLight(i)->Get_Dir()), 1);
			direction = transmat * direction;
			direction = glm::scale(glm::vec3(80, 80, 80)) * direction + p;
			DrawLine(glm::vec2(p.x, p.y), glm::vec2(direction.x, direction.y), glm::vec3(1, 1, 1));
			DrawLine(glm::vec2(p.x + 10, p.y), glm::vec2(direction.x + 10, direction.y), glm::vec3(1, 1, 1));

		}
	}

}

void Renderer::Render(Scene& scene)
{
	int cameraCount = scene.GetCameraCount();
	if (cameraCount > 0)
	{
		int modelCount = scene.GetModelCount();
		const Camera& camera = scene.GetActiveCamera();
		glm::vec3 ambient_l[5];
		glm::vec3 diffuse_l[5];
		glm::vec3 specular_l[5];
		glm::vec3 p_l[5];
		glm::vec3 d_l[5];
		glm::mat4 t_l[5];
		float type_l[5];
		if (scene.Get_count_ofLights())
		{
			DrawLights(scene, glm::mat4(1), glm::mat4(1), glm::mat4(1), glm::mat4(1));
		}
		for (int currentModelIndex = 0; currentModelIndex < modelCount; currentModelIndex++)
		{
			std::shared_ptr<MeshModel> currentModel = scene.GetModel(currentModelIndex);

			for (int i = 0; i < scene.Get_count_ofLights(); i++)
			{
				std::shared_ptr<Light> currentLight = scene.GetLight(i);
				ambient_l[i] = currentLight->Get_A_Color();
				diffuse_l[i] = currentLight->Get_D_Color();
				specular_l[i] = currentLight->Get_S_Color();
				p_l[i] = currentLight->Get_Pos();
				t_l[i] = currentLight->Get_trans_matrix();
				d_l[i] = normalize(currentLight->Get_Dir());
				type_l[i] = currentLight->Get_Type();
			}
		
			colorShader.use();
			colorShader.setUniform("draw", false);
		
			colorShader.setUniform("model", currentModel->get_Transform_Mat());
			colorShader.setUniform("view", camera.get_view_mat() * camera.get_invTransform_Mat());
			colorShader.setUniform("projection", camera.GetProjectionTransformation());
			colorShader.setUniform("eye", camera.get_eye());
			colorShader.setUniform("ambient_l", ambient_l, scene.Get_count_ofLights());
			colorShader.setUniform("diffuse_l", diffuse_l, scene.Get_count_ofLights());
			colorShader.setUniform("specular_l", specular_l, scene.Get_count_ofLights());
			colorShader.setUniform("p_l", p_l, scene.Get_count_ofLights());
			colorShader.setUniform("t_l", t_l, scene.Get_count_ofLights());
			colorShader.setUniform("type_l", type_l, scene.Get_count_ofLights());
			colorShader.setUniform("d_l", d_l, scene.Get_count_ofLights());
			colorShader.setUniform("c", scene.Get_count_ofLights());
			colorShader.setUniform("drawlight", false);
			colorShader.setUniform("ts", scene.GetshadingLight());
			colorShader.setUniform("material.textureMap", 0);
			colorShader.setUniform("material.diffuse", currentModel->Get_modelDiffuse_Color());
			colorShader.setUniform("material.specular", currentModel->Get_modelSpecular_Color());
			colorShader.setUniform("material.ambient", currentModel->Get_modelAmbient_Color());
			colorShader.setUniform("material.alpha", 2.f); // 
			// Set 'texture1' as the active texture at slot #0
			//texture1.bind(0);

			texture1.bind(0);

			// Drag our model's faces (triangles) in fill mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBindVertexArray(currentModel->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
			glBindVertexArray(0);

			texture1.unbind(0);
			// Unset 'texture1' as the active texture at slot #0
			//texture1.unbind(0);

			//colorShader.setUniform("color", glm::vec3(0, 0, 0));

			// Drag our model's faces (triangles) in line mode (wireframe)
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//glBindVertexArray(currentModel->GetVAO());
			//glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
			//glBindVertexArray(0);
		}
	}
}

void Renderer::LoadShaders()
{
	colorShader.loadShaders("vshader.glsl", "fshader.glsl");
}

void Renderer::LoadTextures()
{
	if (!texture1.loadTexture("C:\\projecct\\computer-graphics-2022-nabeeh-rami\\screenshots\\A3\\2.jpeg", true))
	{
		texture1.loadTexture("C:\\projecct\\computer-graphics-2022-nabeeh-rami\\screenshots\\A3\\2.jpeg", true);
	}
}