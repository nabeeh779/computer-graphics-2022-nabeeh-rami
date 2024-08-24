#define _USE_MATH_DEFINES
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"


/**
 * Fields
 */
int LightType;
bool show_demo_window = false;
bool show_another_window = false;
glm::vec4 clear_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
bool local_frame_trans = false;
bool world_frame_trans = false;
bool scaling = false;
bool translation = false;
bool rotation = false;
bool A_X = false;
bool A_Y = false;
bool A_Z = false;
bool show_transformations_window = false;
bool cam_translation = false;
bool cam_rotation = false;
bool cam_A_X = false;
bool cam_A_Y = false;
bool cam_A_Z = false;
bool local_cam_frame_trans = false;
bool world_cam_frame_trans = false;
bool orthographic_projection = true;
bool perspective_projection = false;
bool show_light_window = false;

static float w_s_arry[3] = { 1.0f, 1.0f, 1.0f };
static float w_t_arry[3] = { 0.0f, 0.0f, 0.0f };
static float l_s_arry[3] = { 1.0f, 1.0f, 1.0f };
static float l_t_arry[3] = { 0.0f, 0.0f, 0.0f };
static float angle_x_w = 0.0f;
static float angle_y_w = 0.0f;
static float angle_z_w = 0.0f;
static float angle_x_l = 0.0f;
static float angle_y_l = 0.0f;
static float angle_z_l = 0.0f;
static float last_angle_x_w = 0.0f;
static float last_angle_y_w = 0.0f;
static float last_angle_z_w = 0.0f;
static float last_angle_x_l = 0.0f;
static float last_angle_y_l = 0.0f;
static float last_angle_z_l = 0.0f;
static float w_last_s_arry[3] = { 2.0f, 2.0f, 2.0f };
static float w_last_t_arry[3] = { 2.0f, 2.0f, 2.0f };
static float l_last_s_arry[3] = { 2.0f, 2.0f, 2.0f };
static float l_last_t_arry[3] = { 2.0f, 2.0f, 2.0f };
static int c = 0;
static int reset = 0;
static int bb = 0;
static int light_mode_flag = 0;
static int versNF = 0;
static int faceNF = 0;
static int cc = 0;
static int pro = 0;
static int reset_c = 0;
static float w_cam_t_arry[3] = { 0, 0, 0 };
static float l_cam_t_arry[3] = { 0, 0, 0 };
static float w_last_cam_t_arry[3] = { 0.0f, 0.0f, 0.0f };
static float l_last_cam_t_arry[3] = { 0.0f, 0.0f, 0.0f };
static float cam_angle_x_w = 0.0f;
static float cam_angle_z_w = 0.0f;
static float cam_angle_x_l = 0.0f;
static float cam_angle_y_l = 0.0f;
static float cam_angle_z_l = 0.0f;
static float cam_angle_y_w = 0.0f;

static float last_cam_angle_x_w = 0.0f;
static float last_cam_angle_y_w = 0.0f;
static float last_cam_angle_z_w = 0.0f;
static float last_cam_angle_x_l = 0.0f;
static float last_cam_angle_y_l = 0.0f;
static float last_cam_angle_z_l = 0.0f;

static float eye_arry[3] = { 0.0f, 0.0f, 2.0f };
static float at_arry[3] = { 0.0f, 0.0f, 0.0f };
static float up_arry[3] = { 0.0f, 1.0f, 0.0f };

static float orth_width = 0.5;
static float fov = 10;

static float orth_width_beet = 20;
static float orth_width_dol = 1000;
static float dol_fov = 270;
static float bunny_fov = 60;
static int draw_flag = 0;


static float ambient_model_color[3] = { 1.0f, 1.0f, 1.0f };
static float diffuse_model_color[3] = { 1.0f, 1.0f, 1.0f };
static float specular_model_color[3] = { 1.0f, 1.0f, 1.0f };
bool Tm_light = false, Rm_light = false;
bool Tw_light = false, Rw_light = false;

/**
 * Function declarations
 */
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
void StartFrame();
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void DrawImguiMenus(ImGuiIO& io, Scene& scene);

/**
 * Function implementation
 */
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	// TODO: Handle mouse scroll here
}

int main(int argc, char** argv)
{
	int windowWidth = 1280, windowHeight = 720;
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
	if (!window)
		return 1;

	gladLoadGL();

	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	Renderer renderer = Renderer(frameBufferWidth, frameBufferHeight);
	renderer.LoadShaders();
	renderer.LoadTextures();
	Scene scene = Scene();
	glm::vec2(0, 1);

	ImGuiIO& io = SetupDearImgui(window);
	gladLoadGL();
	glfwSetScrollCallback(window, ScrollCallback);
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		
		StartFrame();
		DrawImguiMenus(io, scene);
		RenderFrame(window, scene, renderer, io);
		glfwPollEvents();

	}

	Cleanup(window);
	return 0;
}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{
	ImGui::Render();
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);



	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
	{
		// TODO: Set new aspect ratio
	}

	if (!io.WantCaptureKeyboard)
	{
		// TODO: Handle keyboard events here
		if (io.KeysDown[65])
		{
			// A key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
		}
	}

	if (!io.WantCaptureMouse)
	{
		// TODO: Handle mouse events here
		if (io.MouseDown[0])
		{
			// Left mouse button is down
		}
	}

	//renderer.ClearColorBuffer(clear_color);
	double setD = 20.0f;
	for (int i = 0; i < 80; i++)
	{
		if (setD > 0)
		{
			setD = setD - 0.25f;
		}
	}
	float setLoopVar = frameBufferWidth;
	float setLoopHorizontal = frameBufferHeight;
	renderer.Render(scene);
	//renderer.SwapBuffers();
	renderer.Set_ZBuffer();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	/**
	 * MeshViewer menu
	 */
	ImGui::Begin("MeshViewer Menu");

	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "CTRL+O"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					scene.AddModel(Utils::LoadMeshModel(outPath));
					scene.AddCamera(std::make_shared<Camera>());
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			ImGui::EndMenu();
		}

		// TODO: Add more menubar items (if you want to)
		ImGui::EndMainMenuBar();
	}

	// Controls
	ImGui::ColorEdit3("Clear Color", (float*)&clear_color);
	// TODO: Add more controls as needed

	ImGui::End();

	/**
	 * Imgui demo - you can remove it once you are familiar with imgui
	 */

	 // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hey there");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Never mind lets work ");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		if (scene.GetModelCount())
		{
			ImGui::Checkbox("Transformations Window", &show_transformations_window);
		}
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
	if (show_transformations_window) {
		ImGui::Begin("Transformations Window", &show_transformations_window);
		/********************************/

		if (scene.GetModelCount()) {

			if (ImGui::Button("show bounding box"))
				bb++;
			if (bb % 2 == 0) {
				scene.GetActiveModel()->set_show_box_flag(0);
			}
			else scene.GetActiveModel()->set_show_box_flag(1);

			if (ImGui::Button("show face Normals"))
				faceNF++;
			if (faceNF % 2 == 0) {
				scene.GetActiveModel()->set_facenorm_flag(0);
			}
			else scene.GetActiveModel()->set_facenorm_flag(1);

			if (ImGui::Button("show verticses Normals"))
				versNF++;
			if (versNF % 2 == 0) {
				scene.GetActiveModel()->set_vernorm_flag(0);
			}
			else scene.GetActiveModel()->set_vernorm_flag(1);


			if (ImGui::Button("Reset"))
				reset = 1;
			if (ImGui::Button("change frame")) {
				c++;
				scaling = 0;
				translation = 0;
				rotation = 0;
				A_X = 0;
				A_Y = 0;
				A_Z = 0;
			}
			if (c % 2 == 0) {
				world_frame_trans = 1;
				local_frame_trans = 0;
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 0, 1, 1), "world frame");
			}
			else {
				local_frame_trans = 1;
				world_frame_trans = 0;
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 0, 1, 1), "local frame");
			}

			if (reset == 1) {
				reset = 0;
				scene.GetActiveModel()->set_Transform_Mat(1);
				local_frame_trans = 0;
				world_frame_trans = 0;
				scaling = 0;
				translation = 0;
				rotation = 0;
				A_X = 0;
				A_Y = 0;
				A_Z = 0;
				w_s_arry[0] = 1;
				w_s_arry[1] = 1;
				w_s_arry[2] = 1;
				w_t_arry[0] = 0;
				w_t_arry[1] = 0;
				w_t_arry[2] = 0;

				l_s_arry[0] = 1;
				l_s_arry[1] = 1;
				l_s_arry[2] = 1;
				l_t_arry[0] = 0;
				l_t_arry[1] = 0;
				l_t_arry[2] = 0;
				angle_x_w = 0.0f;
				angle_z_w = 0.0f;
				angle_x_l = 0.0f;
				angle_y_l = 0.0f;
				angle_z_l = 0.0f;
				c = 0;
				bb = 0;
				versNF = 0;
				faceNF = 0;

			}
			if (local_frame_trans || world_frame_trans) {
				ImGui::TextColored(ImVec4(0, 1, 1, 1), "choose a transformation:");
				ImGui::Checkbox("Scaling", &scaling);
				ImGui::Checkbox("Rotation", &rotation);
				ImGui::Checkbox("Translation", &translation);


				if (scaling) {
					if (world_frame_trans) {
						ImGui::InputFloat("X", &w_s_arry[0]);
						ImGui::InputFloat("Y", &w_s_arry[1]);
						ImGui::InputFloat("Z", &w_s_arry[2]);
					}
					else {
						ImGui::InputFloat("X", &l_s_arry[0]);
						ImGui::InputFloat("Y", &l_s_arry[1]);
						ImGui::InputFloat("Z", &l_s_arry[2]);
					}
					if (world_frame_trans) {
						if (w_s_arry[0] != w_last_s_arry[0])
							w_last_s_arry[0] = w_s_arry[0];
						if (w_s_arry[1] != w_last_s_arry[1])
							w_last_s_arry[1] = w_s_arry[1];
						if (w_s_arry[2] != w_last_s_arry[2])
							w_last_s_arry[2] = w_s_arry[2];
						scene.GetActiveModel()->set_scaling_w(w_s_arry[0], w_s_arry[1], w_s_arry[2]);

					}

					else {
						if (l_s_arry[0] != l_last_s_arry[0])
							l_last_s_arry[0] = l_s_arry[0];
						if (l_s_arry[1] != l_last_s_arry[1])
							l_last_s_arry[1] = l_s_arry[1];
						if (l_s_arry[2] != l_last_s_arry[2])
							l_last_s_arry[2] = l_s_arry[2];
						scene.GetActiveModel()->set_scaling_L(l_s_arry[0], l_s_arry[1], l_s_arry[2]);
					}
				}


				if (translation) {
					if (world_frame_trans) {
						ImGui::InputFloat("X", &w_t_arry[0]);
						ImGui::InputFloat("Y", &w_t_arry[1]);
						ImGui::InputFloat("Z", &w_t_arry[2]);
					}
					else {
						ImGui::InputFloat("X", &l_t_arry[0]);
						ImGui::InputFloat("Y", &l_t_arry[1]);
						ImGui::InputFloat("Z", &l_t_arry[2]);
					}
					if (world_frame_trans) {
						if (w_t_arry[0] != w_last_t_arry[0])
							w_last_t_arry[0] = w_t_arry[0];
						if (w_t_arry[1] != w_last_t_arry[1])
							w_last_t_arry[1] = w_t_arry[1];
						if (w_t_arry[2] != w_last_t_arry[2])
							w_last_t_arry[2] = w_t_arry[2];
						scene.GetActiveModel()->set_translation_w(w_t_arry[0], w_t_arry[1], w_t_arry[2]);



					}
					else {
						if (l_t_arry[0] != l_last_t_arry[0])
							l_last_t_arry[0] = l_t_arry[0];
						if (l_t_arry[1] != l_last_t_arry[1])
							l_last_t_arry[1] = l_t_arry[1];
						if (l_t_arry[2] != l_last_t_arry[2])
							l_last_t_arry[2] = l_t_arry[2];
						scene.GetActiveModel()->set_translation_L(l_t_arry[0], l_t_arry[1], l_t_arry[2]);



					}
				}

				if (rotation) {
					ImGui::TextColored(ImVec4(1, 1, 0, 1), "choose a axis of rotation:");
					ImGui::Checkbox("axis X", &A_X);
					ImGui::Checkbox("axis Y", &A_Y);
					ImGui::Checkbox("axis Z", &A_Z);

					if (A_X == 1) {
						if (world_frame_trans) {
							ImGui::SliderFloat("angle_x", &angle_x_w, -360.0f, 360.0f);
							if (angle_x_w != last_angle_x_w) {
								last_angle_x_w = angle_x_w;
								scene.GetActiveModel()->set_rotation_w(glm::radians(angle_x_w), 1, 0, 0);
							}
						}
						else {
							ImGui::SliderFloat("angle_x", &angle_x_l, -360.0f, 360.0f);
							if (angle_x_l != last_angle_x_l) {
								last_angle_x_l = angle_x_l;
								scene.GetActiveModel()->set_rotation_L(glm::radians(angle_x_l), 1, 0, 0);
							}
						}
					}
					if (A_Y == 1) {
						if (world_frame_trans) {
							ImGui::SliderFloat("angle_y", &angle_y_w, -360.0f, 360.0f);
							if (angle_y_w != last_angle_y_w) {
								last_angle_y_w = angle_y_w;
								scene.GetActiveModel()->set_rotation_w(glm::radians(angle_y_w), 0, 1, 0);
							}
						}
						else {
							ImGui::SliderFloat("angle_y", &angle_y_l, -360.0f, 360.0f);
							if (angle_y_l != last_angle_y_l) {
								last_angle_y_l = angle_y_l;
								scene.GetActiveModel()->set_rotation_L(glm::radians(angle_y_l), 0, 1, 0);
							}
						}
					}
					if (A_Z == 1) {
						if (world_frame_trans) {
							ImGui::SliderFloat("angle_z", &angle_z_w, -360.0f, 360.0f);
							if (angle_z_w != last_angle_z_w) {
								last_angle_z_w = angle_z_w;
								scene.GetActiveModel()->set_rotation_w(glm::radians(angle_z_w), 0, 0, 1);
							}
						}
						else {
							ImGui::SliderFloat("angle_z", &angle_z_l, -360.0f, 360.0f);
							if (angle_z_l != last_angle_z_l) {
								last_angle_z_l = angle_z_l;
								scene.GetActiveModel()->set_rotation_L(glm::radians(angle_z_l), 0, 0, 1);
							}
						}
					}
				}

			}
		}

		if (ImGui::Button("Close Me"))
			show_transformations_window = false;
		ImGui::End();
	}

	if (scene.GetModelCount())
	{
		static float orth_width = scene.GetActiveModel()->Get_orthoGraphicVal();
		ImGui::Begin("Camera Transformation Window");
		if (ImGui::Button("change projection"))
			pro++;

		if (pro % 2 == 0)
		{
			orthographic_projection = 1;
			perspective_projection = 0;
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "Orthographic Projection");
			if (scene.GetActiveModel()->GetModelName() == "banana.obj")
			{
				ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0.01f, 5.0f);
			}

			if (scene.GetActiveModel()->GetModelName() == "beethoven.obj")
			{
				ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0.1f, 100.0f);
				orth_width = orth_width;
			}

			if (scene.GetActiveModel()->GetModelName() == "bishop.obj")
			{
				ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0.1f, 3.0f);
			}

			if (scene.GetActiveModel()->GetModelName() == "blob.obj")
			{
				ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0.1, 200);
				orth_width = orth_width;
			}

			if (scene.GetActiveModel()->GetModelName() == "bunny.obj")
			{
				ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0.1, 20);
				orth_width = orth_width;
			}

			if (scene.GetActiveModel()->GetModelName() == "camera.obj")
			{
				ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0.1, 50);
				//orth_width = orth_width_beet;
			}

			if (scene.GetActiveModel()->GetModelName() == "chain.obj")
			{
				ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0.1, 40);
				orth_width = orth_width;
			}

			if (scene.GetActiveModel()->GetModelName() == "cow.obj")
			{
				ImGui::SliderFloat("Orthographic projection width", &orth_width, 0.1, 50);
				orth_width = orth_width;
			}

			if (scene.GetActiveModel()->GetModelName() == "demo.obj")
			{

				ImGui::SliderFloat("Orthographic projection width", &orth_width, 0.1, 50);
				orth_width = orth_width;
			}

			if (scene.GetActiveModel()->GetModelName() == "dolphin.obj")
			{
				ImGui::SliderFloat("Orthographic projection width", &orth_width, 0.1, 2500);
				orth_width = orth_width;
			}

			if (scene.GetActiveModel()->GetModelName() == "feline.obj")
			{
				ImGui::SliderFloat("Orthographic projection width", &orth_width, 0.1, 2500);
				orth_width = orth_width;
			}

			if (scene.GetActiveModel()->GetModelName() == "pawn.obj")
			{
				ImGui::SliderFloat("Orthographic projection width", &orth_width, 0.1, 1);
			}

			if (scene.GetActiveModel()->GetModelName() == "teapot.obj")
			{
				ImGui::SliderFloat("Orthographic projection width", &orth_width, 0.1, 50);
				orth_width = orth_width;
			}
			scene.GetActiveCamera().set_orth_flag(orthographic_projection);
			scene.GetActiveCamera().set_orth(orth_width);
		}
		else {
			orthographic_projection = 0;
			perspective_projection = 1;
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "Perspective Projection");

			if (scene.GetActiveModel()->GetModelName() == "bunny.obj")
			{//5
				ImGui::SliderFloat("perspective projection fovy", &bunny_fov, 0.1, 360);
				fov = bunny_fov;
			}

			else if (scene.GetActiveModel()->GetModelName() == "dolphin.obj") {//10
				ImGui::SliderFloat("perspective projection fovy", &dol_fov, 0.1, 360);
				fov = dol_fov;
			}
			else
				ImGui::SliderFloat("perspective projection fovy", &fov, 0.1, 360);

			scene.GetActiveCamera().set_orth_flag(orthographic_projection);
			scene.GetActiveCamera().set_perspective(glm::radians(fov));
		}

		/*if (ImGui::Button("change color")) {
			draw_flag++;
		}
		if (draw_flag % 2 == 0) {
			scene.GetActiveCamera().set_draw_color(0);
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "gray scale");
		}
		else {
			scene.GetActiveCamera().set_draw_color(1);
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "random colors");
		}
		*/
		if (ImGui::Button("change frame")) {
			cc++;
			cam_translation = 0;
			cam_rotation = 0;
			cam_A_X = 0;
			cam_A_Y = 0;
			cam_A_Z = 0;

		}
		if (cc % 2 == 0) {
			world_cam_frame_trans = 1;
			local_cam_frame_trans = 0;
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "world frame");
		}
		else {
			local_frame_trans = 1;
			world_frame_trans = 0;
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "local frame");
		}

		if (ImGui::Button("Reset"))
			reset_c = 1;
		if (reset_c == 1) {
			reset_c = 0;
			scene.GetActiveCamera().set_invTransform_Mat(1);
			local_cam_frame_trans = 0;
			world_cam_frame_trans = 0;
			cam_translation = 0;
			cam_rotation = 0;
			cam_A_X = 0;
			cam_A_Y = 0;
			cam_A_Z = 0;
			w_cam_t_arry[0] = 0.0f;
			w_cam_t_arry[1] = 0.0f;
			w_cam_t_arry[2] = 0.0f;
			l_cam_t_arry[0] = 0.0f;
			l_cam_t_arry[1] = 0.0f;
			l_cam_t_arry[2] = 0.0f;

			cam_angle_x_w = 0.0f;
			cam_angle_z_w = 0.0f;
			cam_angle_y_w = 0.0f;
			cam_angle_x_l = 0.0f;
			cam_angle_y_l = 0.0f;
			cam_angle_z_l = 0.0f;
			cc = 0;
			eye_arry[0] = 0;
			eye_arry[1] = 0;
			eye_arry[2] = 2;
			at_arry[0] = 0;
			at_arry[1] = 0;
			at_arry[2] = 0;
			up_arry[0] = 0;
			up_arry[1] = 1;
			up_arry[2] = 0;

		}
		if (local_cam_frame_trans || world_cam_frame_trans) {
			ImGui::TextColored(ImVec4(0, 1, 1, 1), "choose a transformation:");
			ImGui::Checkbox("Rotation", &cam_rotation);
			ImGui::Checkbox("Translation", &cam_translation);


			if (cam_translation) {
				if (world_cam_frame_trans) {
					ImGui::InputFloat("X", &w_cam_t_arry[0]);
					ImGui::InputFloat("Y", &w_cam_t_arry[1]);
					ImGui::InputFloat("Z", &w_cam_t_arry[2]);

					if (w_cam_t_arry[0] != w_last_cam_t_arry[0])
						w_last_cam_t_arry[0] = w_cam_t_arry[0];
					if (w_cam_t_arry[1] != w_last_cam_t_arry[1])
						w_last_cam_t_arry[1] = w_cam_t_arry[1];
					if (w_cam_t_arry[2] != w_last_cam_t_arry[2])
						w_last_cam_t_arry[2] = w_cam_t_arry[2];
					scene.GetActiveCamera().set_translation_w(w_cam_t_arry[0], w_cam_t_arry[1], w_cam_t_arry[2]);
				}
				else if (local_cam_frame_trans) {

					ImGui::InputFloat("X", &l_cam_t_arry[0]);
					ImGui::InputFloat("Y", &l_cam_t_arry[1]);
					ImGui::InputFloat("Z", &l_cam_t_arry[2]);

					if (l_cam_t_arry[0] != l_last_cam_t_arry[0])
						l_last_cam_t_arry[0] = l_cam_t_arry[0];
					if (l_cam_t_arry[1] != l_last_cam_t_arry[1])
						l_last_cam_t_arry[1] = l_cam_t_arry[1];
					if (l_cam_t_arry[2] != l_last_cam_t_arry[2])
						l_last_cam_t_arry[2] = l_cam_t_arry[2];
					scene.GetActiveCamera().set_translation_L(l_cam_t_arry[0], l_cam_t_arry[1], l_cam_t_arry[2]);
				}
			}

			if (cam_rotation) {
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "choose a axis of rotation:");
				ImGui::Checkbox("axis X", &cam_A_X);
				ImGui::Checkbox("axis Y", &cam_A_Y);
				ImGui::Checkbox("axis Z", &cam_A_Z);

				if (cam_A_X) {
					if (world_cam_frame_trans) {
						ImGui::SliderFloat("angle_x", &cam_angle_x_w, -360.0f, 360.0f);
						if (cam_angle_x_w != last_cam_angle_x_w) {
							last_cam_angle_x_w = cam_angle_x_w;
							scene.GetActiveCamera().set_rotation_w(glm::radians(cam_angle_x_w), 1, 0, 0);
						}
					}
					else
					{
						ImGui::SliderFloat("angle_x", &cam_angle_x_l, -360.0f, 360.0f);
						if (cam_angle_x_l != last_cam_angle_x_l)
						{
							last_cam_angle_x_l = cam_angle_x_l;
							scene.GetActiveCamera().set_rotation_L(glm::radians(cam_angle_x_l), 1, 0, 0);
						}
					}
				}
				if (cam_A_Y)
				{
					if (world_cam_frame_trans)
					{
						ImGui::SliderFloat("angle_y", &cam_angle_y_w, -360.0f, 360.0f);
						if (cam_angle_y_w != last_cam_angle_y_w)
						{
							last_cam_angle_y_w = cam_angle_y_w;
							scene.GetActiveCamera().set_rotation_w(glm::radians(cam_angle_y_w), 0, 1, 0);
						}
					}
					else {
						ImGui::SliderFloat("angle_y", &cam_angle_y_l, -360.0f, 360.0f);
						if (cam_angle_y_l != last_cam_angle_y_l)
						{
							last_cam_angle_y_l = cam_angle_y_l;
							scene.GetActiveCamera().set_rotation_L(glm::radians(cam_angle_y_l), 0, 1, 0);
						}
					}
				}
				if (cam_A_Z)
				{
					if (world_cam_frame_trans)
					{
						ImGui::SliderFloat("angle_z", &cam_angle_z_w, -360.0f, 360.0f);
						if (cam_angle_z_w != last_cam_angle_z_w)
						{
							last_cam_angle_z_w = cam_angle_z_w;
							scene.GetActiveCamera().set_rotation_w(glm::radians(cam_angle_z_w), 0, 0, 1);
						}
					}
					else
					{
						ImGui::SliderFloat("angle_z", &cam_angle_z_l, -360.0f, 360.0f);
						if (cam_angle_z_l != last_cam_angle_z_l)
						{
							last_cam_angle_z_l = cam_angle_z_l;
							scene.GetActiveCamera().set_rotation_L(glm::radians(cam_angle_z_l), 0, 0, 1);
						}
					}
				}



			}
		}
		ImGui::TextColored(ImVec4(0, 1, 1, 1), "Look At:");

		ImGui::TextColored(ImVec4(0, 1, 0, 1), "eye:");
		ImGui::InputFloat("X_eye", &eye_arry[0]);
		ImGui::InputFloat("Y_eye", &eye_arry[1]);
		ImGui::InputFloat("Z_eye", &eye_arry[2]);


		ImGui::TextColored(ImVec4(0, 1, 0, 1), "at:");
		ImGui::InputFloat("X_at", &at_arry[0]);
		ImGui::InputFloat("Y_at", &at_arry[1]);
		ImGui::InputFloat("Z_at", &at_arry[2]);


		ImGui::TextColored(ImVec4(0, 1, 0, 1), "up:");
		ImGui::InputFloat("X_up", &up_arry[0]);
		ImGui::InputFloat("Y_up", &up_arry[1]);
		ImGui::InputFloat("Z_up", &up_arry[2]);

		scene.GetActiveCamera().SetCameraLookAt(glm::vec3(eye_arry[0], eye_arry[1], eye_arry[2]), glm::vec3(at_arry[0], at_arry[1], at_arry[2]),
			glm::vec3(up_arry[0], up_arry[1], up_arry[2]));

		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.8f, 0.8f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.8f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.8f, 0.8f, 0.8f));
		int temp123 = ImGui::Button("model with colors");
		ImGui::PopStyleColor(3);
		if (temp123)
		{
			printf("Hi");
			scene.GetActiveModel()->Set_colorbutton(1);
		}

		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.8f, 0.8f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.8f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.8f, 0.8f, 0.8f));
		int temp122 = ImGui::Button("Gray colors");
		ImGui::PopStyleColor(3);
		if (temp122)
		{
			printf("Hi");
			scene.GetActiveModel()->Set_colorbutton(0);
		}

		ImGui::End();
		ImGui::Begin("model");
		static float ambientcolor_m[] = { 0 , 0 , 0 };
		static float diffusecolor_m[] = { 0 , 0 , 0 };
		static float specularcolor_m[] = { 0 , 0 , 0 };
		ImGui::ColorEdit3("ambient color", ambientcolor_m);
		ImGui::ColorEdit3("diffuse color", diffusecolor_m);
		ImGui::ColorEdit3("specular color", specularcolor_m);
		scene.GetActiveModel()->Set_modelAmbient_Color(glm::vec3(ambientcolor_m[0], ambientcolor_m[1], ambientcolor_m[2]));
		scene.GetActiveModel()->Set_modelDiffuse_Color(glm::vec3(diffusecolor_m[0], diffusecolor_m[1], diffusecolor_m[2]));

		scene.GetActiveModel()->Set_modelSpecular_Color(glm::vec3(specularcolor_m[0], specularcolor_m[1], specularcolor_m[2]));
		ImGui::End();
	    ImGui::Begin("Light");
		static int Type = 0;
		static int counter = 0;
		//std::shared_ptr<light> new_light;
		static float ambientcolor[]= { 0 , 0 , 0};
		static float diffusecolor[]= { 0 , 0 , 0};
		static float specularcolor[]={ 0 , 0 , 0};
		static float active_ambientcolor[] = { 0 , 0 , 0 };
		static float active_diffusecolor[] = { 0 , 0 , 0 };
		static float active_specularcolor[] = { 0 , 0 , 0 };
		
		 //char* light_sources_list;
		//static int camera_current_proj = 0;

	    ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "Add light source:\n");
		ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "Type:\n");
		ImGui::RadioButton("Parallel", &LightType, 0);

		ImGui::SameLine();
		ImGui::RadioButton("Point", &LightType, 1);

		ImGui::ColorEdit3("ambient color", ambientcolor);
		ImGui::ColorEdit3("diffuse color", diffusecolor);
		ImGui::ColorEdit3("specular color", specularcolor);
		//ImGui::ColorEdit3("Clear Color", (float*)&clear_color);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3/ 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
		static std::vector <bool> lights;


		if (ImGui::Button("ADD"))
		{
			counter++;
			std::shared_ptr<Light>& new_Light = std::make_shared<Light>(scene.GetActiveModel()->center , LightType + 1);
			(*new_Light).Set_A_Color(glm::vec3(ambientcolor[0], ambientcolor[1], ambientcolor[2]));
			(*new_Light).Set_D_Color(glm::vec3(diffusecolor[0], diffusecolor[1], diffusecolor[2]));
			(*new_Light).Set_S_Color(glm::vec3(specularcolor[0], specularcolor[1], specularcolor[2]));
			//(*new_light).Set_Type(LightType + 1);
			scene.AddLight(new_Light);
			scene.SetActiveLightIndex(0);
			lights.push_back(0);
			//std::make_shared<light>((float*)&ambientcolor, (float*)&diffusecolor, (float*)&specularcolor)
		}
		ImGui::PopStyleColor(3);
		static int flag = 0;
		
		if (ImGui::ListBoxHeader("##", counter, 3))
		{
			for (int n = 0; n < counter; n++)
			{
				char label[32];  sprintf(label, "light %d", n);

				if (ImGui::Selectable(label, lights[n]))
				{
					lights[n] = 1;
					scene.SetActiveLightIndex(n);
					flag = 1;
					
				}
			}
			for (int n = 0; n < counter; n++)
			{
				if(!(scene.GetActiveLightIndex()==n))
					lights[n] = 0;
			}
			ImGui::ListBoxFooter();
		}

		ImGui::Text( "Control active light:\n");
		ImGui::ColorEdit3("active ambient color", active_ambientcolor);
		ImGui::ColorEdit3("active diffuse color", active_diffusecolor);
		ImGui::ColorEdit3("active specular color", active_specularcolor);
		if (scene.Get_count_ofLights())
		{
			scene.GetActiveLight()->Set_A_Color(glm::vec3(active_ambientcolor[0], active_ambientcolor[1], active_ambientcolor[2]));
			scene.GetActiveLight()->Set_D_Color(glm::vec3(active_diffusecolor[0], active_diffusecolor[1], active_diffusecolor[2]));
			scene.GetActiveLight()->Set_S_Color(glm::vec3(active_specularcolor[0], active_specularcolor[1], active_specularcolor[2]));
			static float alpha = 5;
			ImGui::SliderFloat("alpha", &alpha, 1.0f, 10.0f);
			scene.GetActiveLight()->Set_alpha(alpha);

			if (scene.GetActiveLight()->Get_Type() == 1)
			{
				ImGui::Text("Light direction\n");

				static bool inputs_step = true;
				static float  f1_v = 1.0f;
				static float  f2_v = 1.0f;
				static float  f3_v = -1.0f;
				const float    f32_one = 1.f;
				ImGui::Checkbox("Show step buttons", &inputs_step);
				ImGui::InputScalar("X", ImGuiDataType_Float, &f1_v, inputs_step ? &f32_one : NULL);
				ImGui::InputScalar("Y", ImGuiDataType_Float, &f2_v, inputs_step ? &f32_one : NULL);
				ImGui::InputScalar("Z", ImGuiDataType_Float, &f3_v, inputs_step ? &f32_one : NULL);
				scene.GetActiveLight()->Set_Dir(glm::vec3(f1_v, f2_v, f3_v));
			}
			else
			{
				ImGui::Text("Transformations \n");


				const char* listbox_lightTrans[] = { "local transformation","world transformation" };
				const char* listbox_lightrotations[] = { "rotate around x","rotate around y","rotate around z" };
				static int listbox_light_current = 0;
				static int current_lightrotation = 0;


				//static float anglem = 0.0f;
				static float ax_m_light = 0.0f;
				static float lastax_m_light = 0.0f;
				static float ay_m_light = 0.0f;
				static float lastay_m_light = 0.0f;
				static float az_m_light = 0.0f;
				static float lastaz_m_light = 0.0f;


				static float anglew_light = 0.0f;
				static float ax_w_light = 0.0f;
				static float lastax_w_light = 0.0f;
				static float ay_w_light = 0.0f;
				static float lastay_w_light = 0.0f;
				static float az_w_light = 0.0f;
				static float lastaz_w_light = 0.0f;


				static float Tm_vec_light[3] = { 0.0f, 0.0f, 0.0f }; //translate vector to the modle, the vector contains x,y,z steps
				static float Tw_vec_light[3] = { 0.0f, 0.0f, 0.0f }; //translate vector to the world, the vector contains x,y,z steps
				static float Sm_vec_light[3] = { 1.0f, 1.0f, 1.0f }; //scale vector to the modle, the vector contains x,y,z steps
				static float Sw_vec_light[3] = { 1.0f, 1.0f, 1.0f };//scale vector to the world, the vector contains x,y,z steps



				ImGui::ListBox("select\n", &listbox_light_current, listbox_lightTrans, IM_ARRAYSIZE(listbox_lightTrans), 2);
				if (counter != 0 && flag)
				{
					if (listbox_light_current == 0) // local(model)
					{

						ImGui::Checkbox("translation", &Tm_light);
						if (Tm_light)
						{

							ImGui::InputFloat("tranlation x steps", &Tm_vec_light[0]);
							ImGui::InputFloat("tranlation y steps", &Tm_vec_light[1]);
							ImGui::InputFloat("tranlation z steps", &Tm_vec_light[2]);
							scene.GetActiveLight()->Set_Transform_model_mat(glm::translate(glm::vec3(Tm_vec_light[0], Tm_vec_light[1], Tm_vec_light[2])));
							scene.GetActiveLight()->Set_trans_matrix();

						}
						ImGui::Checkbox("Rotation", &Rm_light);
						if (Rm_light)
						{
							ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "select any rotation:\n");
							ImGui::ListBox("", &current_lightrotation, listbox_lightrotations, IM_ARRAYSIZE(listbox_lightrotations), 3);

							ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "set the angle:\n");

							if (current_lightrotation == 0) //around x
							{
								ImGui::SliderAngle("slider angle", &ax_m_light, -360, 360);

								if (lastax_m_light != ax_m_light)
								{
									lastax_m_light = ax_m_light;
									scene.GetActiveLight()->Set_Rotate_model_mat(glm::rotate(ax_m_light, glm::vec3(1, 0, 0)), 0);
									scene.GetActiveLight()->Set_trans_matrix();
								}



							}
							if (current_lightrotation == 1)// around y
							{
								ImGui::SliderAngle("slider angle", &ay_m_light, -360, 360);
								if (lastay_m_light != ay_m_light)
								{
									lastay_m_light = ay_m_light;
									scene.GetActiveLight()->Set_Rotate_model_mat(glm::rotate(ay_m_light, glm::vec3(0, 1, 0)), 1);
									scene.GetActiveLight()->Set_trans_matrix();
								}
							}
							if (current_lightrotation == 2) // around z
							{
								ImGui::SliderAngle("slider angle", &az_m_light, -360, 360);

								if (lastaz_m_light != az_m_light)
								{
									lastaz_m_light = az_m_light;
									scene.GetActiveLight()->Set_Rotate_model_mat(glm::rotate(az_m_light, glm::vec3(0, 0, 1)), 2);
									scene.GetActiveLight()->Set_trans_matrix();
								}


							}

						}



					}
					else //world
					{


						ImGui::Checkbox("translation", &Tw_light);
						if (Tw_light)
						{

							ImGui::InputFloat("tranlation x steps", &Tw_vec_light[0]);
							ImGui::InputFloat("tranlation y steps", &Tw_vec_light[1]);
							ImGui::InputFloat("tranlation z steps", &Tw_vec_light[2]);

							scene.GetActiveLight()->Set_Transform_world_mat(glm::translate(glm::vec3(Tw_vec_light[0], Tw_vec_light[1], Tw_vec_light[2])));
							scene.GetActiveLight()->Set_trans_matrix();
						}
						ImGui::Checkbox("Rotation", &Rw_light);
						if (Rw_light)
						{

							ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "select any rotation:\n");
							ImGui::ListBox("", &current_lightrotation, listbox_lightrotations, IM_ARRAYSIZE(listbox_lightrotations), 3);

							ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "set the angle:\n");

							if (current_lightrotation == 0)
							{
								ImGui::SliderAngle("slider angle", &ax_w_light, -360, 360);

								if (lastax_w_light != ax_w_light)
								{
									lastax_w_light = ax_w_light;
									scene.GetActiveLight()->Set_Rotate_world_mat(glm::rotate(ax_w_light, glm::vec3(1, 0, 0)), 0);
									scene.GetActiveLight()->Set_trans_matrix();
								}



							}
							if (current_lightrotation == 1)
							{
								ImGui::SliderAngle("slider angle", &ay_w_light, -360, 360);
								if (lastay_w_light != ay_w_light)
								{
									lastay_w_light = ay_w_light;
									scene.GetActiveLight()->Set_Rotate_world_mat(glm::rotate(ay_w_light, glm::vec3(0, 1, 0)), 1);
									scene.GetActiveLight()->Set_trans_matrix();
								}
							}
							if (current_lightrotation == 2)
							{
								ImGui::SliderAngle("slider angle", &az_w_light, -360, 360);

								if (lastaz_w_light != az_w_light)
								{
									lastaz_w_light = az_w_light;
									scene.GetActiveLight()->Set_Rotate_model_mat(glm::rotate(az_w_light, glm::vec3(0, 0, 1)), 2);
									scene.GetActiveLight()->Set_trans_matrix();
								}


							}

						}

					}
					scene.GetActiveLight()->Set_trans_matrix();
				}
			}
		}
		static int shadingtype = 2;
		ImGui::RadioButton("texture", &shadingtype,0);
		ImGui::RadioButton("toon shading", &shadingtype,1);
		ImGui::RadioButton("phong", &shadingtype,2);
		scene.Setshading(shadingtype);

		ImGui::End();

	}
}