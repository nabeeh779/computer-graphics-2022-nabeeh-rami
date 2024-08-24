#include "Scene.h"
#include "MeshModel.h"
#include <string>

Scene::Scene() :
	active_camera_index(0),
	active_model_index(0)
{

}

void Scene::AddModel(const std::shared_ptr<MeshModel>& mesh_model)
{
	mesh_models.push_back(mesh_model);
}

int Scene::GetModelCount() const
{
	return mesh_models.size();
}

std::shared_ptr<MeshModel> Scene::GetModel(int index) const
{
	return mesh_models[index];
}

std::shared_ptr<MeshModel> Scene::GetActiveModel() const
{
	return mesh_models[active_model_index];
}



void Scene::AddCamera(const std::shared_ptr<Camera>& camera)
{
	cameras.push_back(camera);
}

int Scene::GetCameraCount() const
{
	return cameras.size();
}

Camera& Scene::GetCamera(int index)
{
	return *cameras[index];
}

Camera& Scene::GetActiveCamera() const
{
	return *cameras[active_camera_index];
}

void Scene::SetActiveCameraIndex(int index)
{
	active_camera_index = index;
}

int Scene::GetActiveCameraIndex() const
{
	return active_camera_index;
}

void Scene::SetActiveModelIndex(int index)
{
	active_model_index = index;
}

int Scene::GetActiveModelIndex() const
{
	return active_model_index;
}

void Scene::AddLight(const std::shared_ptr<Light>& light)
{
	lights_.push_back(light);
	count_oflights = count_oflights + 1;
}

void Scene::SetActiveLightIndex(int index)
{
	active_light_index_ = index;
}


int Scene::GetActiveLightIndex() const
{
	return active_light_index_;
}

std::shared_ptr<Light> Scene::GetActiveLight() const
{
	return lights_[active_light_index_];
}

int Scene::Get_count_ofLights() const
{
	return this->count_oflights;
}

std::shared_ptr<Light> Scene::GetLight(int index) const
{
	return lights_[index];
}

int Scene::GetshadingLight() const
{
	return shading;
}
void Scene::Setshading(int index)
{
	shading = index;
}