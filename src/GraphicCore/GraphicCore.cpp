#include "GraphicCore.h"

wnd::Window* CreateWindow(const size_t w, const size_t h, const char* title)
{
	return new wnd::Window(w, h, title);
}

void CreateWindow(wnd::Window* window)
{
	if (window) {
		delete window;
	}
}

gapi::Gapi* CreateGapi(wnd::Window* window)
{
	return new gapi::Gapi(*window);
}

gapi::Scene* CreateScene(gapi::Gapi* gapi)
{
	return gapi->CreateScene();
}

void DeleteScene(gapi::Gapi* gapi, gapi::Scene* scene)
{
	gapi->DeleteScene(scene);
}

void SceneAddGeometry(gapi::Scene* scene, gapi::Geometry* geometry)
{
	scene->AddGeometry(geometry);
}

void SceneRemoveGeometry(gapi::Scene* scene, gapi::Geometry* geometry)
{
	scene->RemoveGeometry(geometry);
}

gapi::RenderPass* CreateRenderPass(gapi::Gapi* gapi, llr::Shader* shader) {
	return gapi->CreateRenderPass( * shader );
}

void DeleteRenderPass(gapi::Gapi* gapi, gapi::RenderPass* renderPass) {
	gapi->DeleteRenderPass(renderPass);
}

gapi::Geometry* CreateGeometry(gapi::Gapi* gapi, float* vertices, size_t vertexN, unsigned int* indexes, size_t indexN) {
	std::vector<float> vertexV(vertexN);
	std::memcpy(vertexV.data(), vertices, vertexV.size() * sizeof(vertexV[0]));

	std::vector<unsigned int> indexV(indexN);
	std::memcpy(indexV.data(), indexes, indexV.size() * sizeof(indexV[0]));

	return gapi->CreateGeometry(vertexV, indexV);
}

void DeleteGeometry(gapi::Gapi* gapi, gapi::Geometry * geometry) {
	gapi->DeleteGeometry(geometry);
}

void Draw(gapi::Gapi* gapi, gapi::Scene* scene)
{
	gapi->Draw(scene);
}
