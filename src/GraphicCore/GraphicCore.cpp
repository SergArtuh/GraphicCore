#include "GraphicCore.h"

#include <list>
#include<stdarg.h>

wnd::Window* CreateWindow(const size_t w, const size_t h, const char* title)
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

gapi::Shader* CreateShader(gapi::Gapi* gapi, int count, int type, const char* const source, ...) {
	if (count <= 0) {
		return nullptr;
	}

	std::list< gapi::ShaderSource> shaderSources;

	va_list arg;
	va_start(arg, count);
	for (int i = 0; i < count; ++i) {
		auto type = va_arg(arg, int);
		auto src = va_arg(arg, const char* const);
		shaderSources.emplace_back(src, type);
	}

	va_end(arg);
	return gapi->CreateShader(shaderSources);
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

void Draw(gapi::Gapi* gapi, gapi::Context* context, gapi::Scene* scene)
{
	gapi->Draw(context, scene);
}
