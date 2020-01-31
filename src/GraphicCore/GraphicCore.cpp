#include "GraphicCore.h"

#include <list>
#include<stdarg.h>

wnd::Window* CreateWindow(const size_t w, const size_t h, CStr title)
{
	return new wnd::Window(w, h, title);
}

void DeleteWindow(wnd::Window* window)
{
	if (window) {
		delete window;
	}
}

gapi::Gapi* CreateGapi(wnd::Window* window)
{
	return new gapi::Gapi(*window);
}

gapi::Context* CreateContext(gapi::Gapi* gapi)
{
	return gapi->CreateContext();
}

void DeleteContext(gapi::Gapi* gapi, gapi::Context* context) {
	gapi->DeleteContext(context);
}

void ContextAddRenderPass(gapi::Gapi* gapi, gapi::Context* context, gapi::RenderPass* renderPass)
{
	gapi->ContextAddRenderPass(context, renderPass);
}

void ContextRemoveRenderPass(gapi::Gapi* gapi, gapi::Context* context, gapi::RenderPass* renderPass)
{
	gapi->ContextRemoveRenderPass(context, renderPass);
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

gapi::ShaderSource* CreateShaderSource(CStr sourcr, int32_t type)
{
	return new gapi::ShaderSource(sourcr, gapi::ShaderSourceType(type));
}

void DeleteShaderSource(gapi::ShaderSource* shaderSource)
{
	if (shaderSource) {
		delete shaderSource;
	}
}

gapi::Shader* CreateShader(gapi::Gapi* gapi, gapi::ShaderSource ** sources, uint32_t count) {
	if (!(sources && count > 0)) {
		return nullptr;
	}
	std::list< gapi::ShaderSource> sourcesList;
	for (int i = 0; i < count; ++i) {
		sourcesList.push_back(*sources[i]);
	}

	return gapi->CreateShader(sourcesList);
}

void DeleteShader(gapi::Gapi* gapi, gapi::Shader* shader) {
	gapi->DeleteShader(shader);
}

gapi::RenderPass* CreateRenderPass(gapi::Gapi* gapi, gapi::Shader * shader) {
	return gapi->CreateRenderPass( shader );
}

void DeleteRenderPass(gapi::Gapi* gapi, gapi::RenderPass* renderPass) {
	gapi->DeleteRenderPass(renderPass);
}

gapi::Geometry* CreateGeometry(gapi::Gapi* gapi, float* vertices, CSize vertexN, uint32_t * indexes, CSize indexN) {
	std::vector<float> vertexV(vertexN);
	std::memcpy(vertexV.data(), vertices, vertexV.size() * sizeof(vertexV[0]));

	std::vector<unsigned int> indexV(indexN);
	std::memcpy(indexV.data(), indexes, indexV.size() * sizeof(indexV[0]));

	return gapi->CreateGeometry(vertexV, indexV);
}

void DeleteGeometry(gapi::Gapi* gapi, gapi::Geometry * geometry) {
	gapi->DeleteGeometry(geometry);
}

void Draw(gapi::Gapi* gapi, gapi::Context* context, gapi::Scene* scene)
{
	gapi->Draw(context, scene);
}
