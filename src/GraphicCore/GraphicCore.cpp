#include "GraphicCore.h"

#include <list>
#include<stdarg.h>

#include "gapi/enum.h"

#include "common/Logger.h"


class GraphicCoreLogStrategy : public common::ILoggerStrategy {
public:
	virtual void Log(const char const* msg) override {
		m_callback(msg);
	}

	void SetCallback(LogMsgCallback callback) {
		m_callback = callback;
	}
private:
	LogMsgCallback m_callback = nullptr;
};


wnd::Window* CreateWindow(const CSize w, const CSize h, CStr title) {
	return new wnd::Window(w, h, title);
}

void DeleteWindow(wnd::Window* window)
{
	if (window) {
		delete window;
	}
}

gapi::PGapi CreateGapi(wnd::Window* window) {
	return new gapi::Gapi(*window);
}

gapi::Context* CreateContext(gapi::PGapi gapi)
{
	return gapi->CreateContext();
}

void DeleteContext(gapi::PGapi gapi, gapi::Context* context) {
	gapi->DeleteContext(context);
}

void ContextAddRenderPass(gapi::PGapi gapi, gapi::Context* context, gapi::RenderPass* renderPass)
{
	gapi->ContextAddRenderPass(context, renderPass);
}

void ContextRemoveRenderPass(gapi::PGapi gapi, gapi::Context* context, gapi::RenderPass* renderPass)
{
	gapi->ContextRemoveRenderPass(context, renderPass);
}

gapi::Scene* CreateScene(gapi::PGapi gapi)
{
	return gapi->CreateScene();
}

void DeleteScene(gapi::PGapi gapi, gapi::Scene* scene)
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

gapi::Shader* CreateShader(gapi::PGapi gapi, gapi::ShaderSource ** sources, UI32 count) {
	if (!(sources && count > 0)) {
		return nullptr;
	}
	std::list< gapi::ShaderSource> sourcesList;
	for (int i = 0; i < count; ++i) {
		sourcesList.push_back(*sources[i]);
	}

	return gapi->CreateShader(sourcesList);
}

void DeleteShader(gapi::PGapi gapi, gapi::Shader* shader) {
	gapi->DeleteShader(shader);
}

gapi::PTexture2D CreateTexture2D(gapi::PGapi gapi, CSize width, CSize height, I32 format)
{
	return gapi->CreateTexture2d(width, height, static_cast<gapi::ETextureFormat>(format));
}

void DeleteTexture2D(gapi::PGapi gapi, gapi::PTexture2D texture2d)
{
	if (texture2d) {
		delete texture2d;
	}
}


void WriteTexture2D(gapi::PTexture2D texture2d, CSize xMin, const CSize xMax, CSize yMin, CSize yMax, CData data) {
	texture2d->Write(xMin, xMax,yMin, yMax, data);
}

void SaveTexture2D(gapi::PGapi gapi, gapi::PTexture2D texture2d, CStr path)
{
	const std::string pathStr(path);
	texture2d->Save(pathStr);
}

gapi::RenderPassInput* CreateRenderPassInput(gapi::PGapi gapi, CSize size) {
	return gapi->CreateRenderPassInput(size);
}

void DeleteRenderPassInput(gapi::PGapi gapi, gapi::RenderPassInput* renderPassInput) {
	gapi->DeleteRenderPassInput(renderPassInput);
}

void* GetRenderPassInputDataNativePtr(gapi::RenderPassInput* renderPassInput) {
	return renderPassInput->GetData().data();
}

void MarkDirtyRenderPassInput(gapi::RenderPassInput* renderPassInput) {
	renderPassInput->Update();
}

gapi::RenderPassStage* CreateRenderPassStage(gapi::PGapi gapi)
{
	return gapi->CreateRenderPassStage();
}

void SetRenderPassStageTexture2d(gapi::PGapi gapi, gapi::PRenderPassStage renderPass, gapi::PTexture2D texture2d, UI32 location) {
	renderPass->SetTexture2D(texture2d, location);
}

void DeleteRenderPassStage(gapi::PGapi gapi, gapi::PRenderPassStage renderPassStage)
{
	gapi->DeleteRenderPassStage(renderPassStage);
}

void SetRenderPassStageInput(gapi::PGapi gapi, gapi::PRenderPassStage renderPassStage, gapi::RenderPassInput* renderPassInput, UI32 location)
{
	gapi->SetRenderPassStageInput(renderPassStage, renderPassInput, location);
}

void SetRenderPassStageGeometryTarget(gapi::PRenderPassStage renderPassStage, int target) {
	renderPassStage->SetGeometryTarget(static_cast<gapi::ERenderPassInputGeometryTarget>(target));
}

void AddRenderPassStageGeometry(gapi::PRenderPassStage renderPassStage, gapi::Geometry* geometry) {
	renderPassStage->AddGeomerty(geometry);
}

void RemoveRenderPassStageGeometry(gapi::PRenderPassStage renderPassStage, gapi::Geometry* geometry) {
	renderPassStage->RemoveGeomerty(geometry);
}

gapi::RenderPass* CreateRenderPass(gapi::PGapi gapi, gapi::Shader * shader) {
	return gapi->CreateRenderPass( shader );
}

void DeleteRenderPass(gapi::PGapi gapi, gapi::RenderPass* renderPass) {
	gapi->DeleteRenderPass(renderPass);
}

void AddRenderPassStage(gapi::RenderPass* renderPass, gapi::RenderPassStage* stage) {
	renderPass->AddRenderPassStage(stage);
}

gapi::Camera* CreateCamera(gapi::PGapi gapi, float fow, float aspect, float near, float far) {
	return gapi->CreateCamera(fow, aspect, near, far);
}

void DeleteCamera(gapi::PGapi gapi, gapi::Camera * camere) {
	gapi->DeleteCamera(camere);
}

gapi::Geometry* CreateGeometry(gapi::PGapi gapi, float* vertices, CSize vertexN, UI32 * indexes, CSize indexN) {
	std::vector<float> vertexV(vertexN);
	std::memcpy(vertexV.data(), vertices, vertexV.size() * sizeof(vertexV[0]));

	std::vector<unsigned int> indexV(indexN);
	std::memcpy(indexV.data(), indexes, indexV.size() * sizeof(indexV[0]));

	return gapi->CreateGeometry(vertexV, indexV);
}

void DeleteGeometry(gapi::PGapi gapi, gapi::Geometry * geometry) {
	gapi->DeleteGeometry(geometry);
}

void Draw(gapi::PGapi gapi, gapi::Context* context, gapi::Scene* scene)
{
	gapi->Draw(context, scene);
}




void SetLogCallback(LogMsgCallback callback) {
	auto logStrategy = new GraphicCoreLogStrategy();
	logStrategy->SetCallback(callback);
	common::Logger::Get().SetStrategy(logStrategy);
}
