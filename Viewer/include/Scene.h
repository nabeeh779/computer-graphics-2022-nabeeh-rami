#pragma once

#include <vector>
#include <memory>
#include "Light.h"
#include "Camera.h"
#include "MeshModel.h"

using namespace std;

class Scene
{
public:
	Scene();

	void AddModel(const shared_ptr<MeshModel>& mesh_model);
	int GetModelCount() const;
	std::shared_ptr<MeshModel> GetModel(int index) const;
	std::shared_ptr<MeshModel> GetActiveModel() const;

	//MeshModel& GetActiveModel() const;
	//MeshModel& GetModel(int index) const;



	void AddCamera(const shared_ptr<Camera>& camera);
	int GetCameraCount() const;
	Camera& GetCamera(int index);
	Camera& GetActiveCamera() const;
	void SetActiveCameraIndex(int index);
	int GetActiveCameraIndex() const;
	void SetActiveModelIndex(int index);
	int GetActiveModelIndex() const;

	void AddLight(const std::shared_ptr<Light>& Light);
	void SetActiveLightIndex(int index);
	int GetActiveLightIndex() const;
	std::shared_ptr<Light> GetActiveLight() const;
	int Get_count_ofLights() const;
	std::shared_ptr<Light> GetLight(int index) const;
	int GetshadingLight() const;
	void Setshading(int index);
private:
	std::vector<shared_ptr<MeshModel>> mesh_models;
	vector<shared_ptr<Camera>> cameras;
	std::vector<std::shared_ptr<Light>> lights_;
	int active_camera_index;
	int active_model_index;
	int active_light_index_;
	int shading = 0;
	int count_oflights = 0;
	int fog = 0; // 0 linear , 1 e
	float FogDensity = 5;
};