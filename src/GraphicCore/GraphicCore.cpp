#include "GraphicCore.h"

#include <list>
#include<stdarg.h>

#include "gapi/enum.h"

wnd::Window* CreateWindow(const CSize w, const CSize h, CStr title)
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

void SceneSetCamera(gapi::Scene* scene, gapi::Camera* camera)
{
	scene->SetCamera(camera);
}

void SceneAddGeometry(gapi::Scene* scene, gapi::Geometry* geometry)
{
	scene->AddGeometry(geometry);
}

void SceneRemoveGeometry(gapi::Scene* scene, gapi::Geometry* geometry)
{
	scene->RemoveGeometry(geometry);
}

gapi::ShaderSource* CreateShaderSource(CStr sourcr, I32 type)
{
	return new gapi::ShaderSource(sourcr, gapi::ShaderSourceType(type));
}

void DeleteShaderSource(gapi::ShaderSource* shaderSource)
{
	if (shaderSource) {
		delete shaderSource;
	}
}

gapi::Shader* CreateShader(gapi::Gapi* gapi, gapi::ShaderSource ** sources, UI32 count) {
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

gapi::RenderPassInput* CreateRenderPassInput(gapi::Gapi* gapi, CSize size) {
	return gapi->CreateRenderPassInput(size);
}

void DeleteRenderPassInput(gapi::Gapi* gapi, gapi::RenderPassInput* renderPassInput) {
	gapi->DeleteRenderPassInput(renderPassInput);
}

void* GetRenderPassInputDataNativePtr(gapi::RenderPassInput* renderPassInput) {
	return renderPassInput->GetData().data();
}

void MarkDirtyRenderPassInput(gapi::RenderPassInput* renderPassInput) {
	renderPassInput->MarkDirty();
}

gapi::RenderPassStage* CreateRenderPassStage(gapi::Gapi* gapi)
{
	return gapi->CreateRenderPassStage();
}

void DeleteRenderPassStage(gapi::Gapi* gapi, gapi::RenderPassStage* renderPassStage)
{
	gapi->DeleteRenderPassStage(renderPassStage);
}

void SetRenderPassStageInput(gapi::Gapi* gapi, gapi::RenderPassStage* renderPassStage, gapi::RenderPassInput* renderPassInput, UI32 location)
{
	gapi->SetRenderPassStageInput(renderPassStage, renderPassInput, location);
}

void SetRenderPassStageGeometryTarget(gapi::RenderPassStage* renderPassStage, int target) {
	renderPassStage->SetGeometryTarget(static_cast<gapi::ERenderPassInputGeometryTarget>(target));
}

void AddRenderPassStageGeometry(gapi::RenderPassStage* renderPassStage, gapi::Geometry* geometry) {
	renderPassStage->AddGeomerty(geometry);
}

void RemoveRenderPassStageGeometry(gapi::RenderPassStage* renderPassStage, gapi::Geometry* geometry) {
	renderPassStage->RemoveGeomerty(geometry);
}

gapi::RenderPass* CreateRenderPass(gapi::Gapi* gapi, gapi::Shader * shader) {
	return gapi->CreateRenderPass( shader );
}

void DeleteRenderPass(gapi::Gapi* gapi, gapi::RenderPass* renderPass) {
	gapi->DeleteRenderPass(renderPass);
}

void AddRenderPassStage(gapi::RenderPass* renderPass, gapi::RenderPassStage* stage) {
	renderPass->AddRenderPassStage(stage);
}

gapi::Camera* CreateCamera(gapi::Gapi* gapi, float fow, float aspect, float near, float far) {
	return gapi->CreateCamera(fow, aspect, near, far);
}

void DeleteCamera(gapi::Gapi* gapi, gapi::Camera * camere) {
	gapi->DeleteCamera(camere);
}

gapi::Geometry* CreateGeometry(gapi::Gapi* gapi, float* vertices, CSize vertexN, UI32 * indexes, CSize indexN) {
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
