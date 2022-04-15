#include "GraphicCore.h"

#include <list>
#include<stdarg.h>

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
	return gapi->CreateTexture2d(width, height, static_cast<ETextureFormat>(format));
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

void LoadTexture2D(gapi::PGapi gapi, gapi::PTexture2D texture2d, CStr path) {
	const std::string pathStr(path);
	texture2d->Load(pathStr);
}

gapi::PRenderPassConstantInput CreateRenderPassConstantInput(gapi::PGapi gapi, CSize size) {
	return gapi->CreateRenderPassInput(size);
}

void DeleteRenderPassConstantInput(gapi::PGapi gapi, gapi::PRenderPassConstantInput renderPassInput) {
	gapi->DeleteRenderPassInput(renderPassInput);
}

void* GetRenderPassConstantInputDataNativePtr(gapi::PRenderPassConstantInput renderPassInput) {
	return renderPassInput->GetData().data();
}

void MarkDirtyRenderPassConstantInput(gapi::PRenderPassConstantInput renderPassInput) {
	renderPassInput->Update();
}

gapi::PRenderPassInstanceArrayInput CreateRenderPassInstanceArrayInput(gapi::PGapi gapi, CSize size, I32 type, CSize count)
{
	return gapi->CreateRenderPassInstanceArrayInput(size, static_cast<EDataType>(type) ,count);
}

void DeleteRenderPassInstanceArrayInput(gapi::PGapi gapi, gapi::PRenderPassInstanceArrayInput instanceArrayInput) {
	gapi->DeleteRenderPassInstanceArrayInput(instanceArrayInput);
}

void WriteRenderPassInstanceArrayInput(gapi::PGapi gapi, gapi::PRenderPassInstanceArrayInput instanceArrayInput, void * arrayData, CSize arrayDataN, CSize offset) {
	instanceArrayInput->Write(offset, arrayDataN, arrayData);
}

gapi::PRenderPassOutput CreateRenderPassOutput(gapi::PGapi gapi) {
	return gapi->CreateRenderPassOutput();
}

void DeleteRenderPassOutput(gapi::PGapi gapi, gapi::PRenderPassOutput renderPassOutput) {
	gapi->DeleteRenderPassOutput(renderPassOutput);
}

void SetRenderPassOutputTexture2d(gapi::PGapi gapi, gapi::PRenderPassOutput renderPassOutput, gapi::PTexture2D texture, UI32 location) {
	renderPassOutput->SetTexture2D(texture, location);
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

void SetRenderPassStageConstantInput(gapi::PGapi gapi, gapi::PRenderPassStage renderPassStage, gapi::PRenderPassConstantInput renderPassInput, UI32 location)
{
	renderPassStage->SetConstantInput(renderPassInput, location);
}

void SetRenderPassStageOutput(gapi::PGapi gapi, gapi::PRenderPassStage renderPassStage, gapi::PRenderPassOutput output) {
	renderPassStage->SetRenderPassOutput(output);
}

void SetRenderPassStageGeometryTarget(gapi::PRenderPassStage renderPassStage, int target) {
	renderPassStage->SetGeometryTarget(static_cast<ERenderPassInputGeometryTarget>(target));
}

void AddRenderPassStageGeometry(gapi::PRenderPassStage renderPassStage, gapi::Geometry* geometry) {
	renderPassStage->AddGeomerty(geometry);
}

void RemoveRenderPassStageGeometry(gapi::PRenderPassStage renderPassStage, gapi::Geometry* geometry) {
	renderPassStage->RemoveGeomerty(geometry);
}

void SetRenderPassInstanceArray(gapi::PRenderPassStage renderPassStage, gapi::PRenderPassInstanceArrayInput instanceArray, CI32 location) {
	renderPassStage->SetRenderPassInstanceArray(instanceArray, location);
}

void SetRenderPassInstanceCount(gapi::PRenderPassStage renderPassStage, CSize count) {
	renderPassStage->SetRenderPassInstanceCount(count);
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

gapi::Geometry* CreateGeometry(gapi::PGapi gapi,
	float* vertices, CSize vertexCount,
	UI32* indexes, CSize indexN,
	float* normals,
	float* uvs,
	float* tangents,
	float* bitangents
) {

	CSize vertexVecLen = 3;
	CSize normalVecLen = 3;
	CSize uvVecLen = 2;
	CSize tangentVecLen = 3;
	CSize bitangentVecLen = 3;


	std::vector<float> vertexV(vertexCount * vertexVecLen);
	std::memcpy(vertexV.data(), vertices, vertexV.size() * sizeof(vertexV[0]));

	std::vector<unsigned int> indexV(indexN);
	std::memcpy(indexV.data(), indexes, indexV.size() * sizeof(indexV[0]));


	// Normals
	std::vector<float> normalV(vertexCount * normalVecLen);

	if (normals) {
		std::memcpy(normalV.data(), normals, normalV.size() * sizeof(normalV[0]));
	}
	else {
		std::fill(normalV.begin(), normalV.end(), 0.f);
	}


	// UV
	std::vector<float> uvV(vertexCount * uvVecLen);

	if (uvs) {
		std::memcpy(uvV.data(), uvs, uvV.size() * sizeof(uvV[0]));
	}
	else {
		std::fill(uvV.begin(), uvV.end(), 0.f);
	}



	// Tangent
	std::vector<float> tangentV(vertexCount * tangentVecLen);

	if (tangents) {
		std::memcpy(tangentV.data(), tangents, tangentV.size() * sizeof(tangentV[0]));
	}
	else {
		std::fill(tangentV.begin(), tangentV.end(), 0.f);
	}


	// Bitangent
	std::vector<float> bitangentV(vertexCount * bitangentVecLen);

	if (bitangents) {
		std::memcpy(bitangentV.data(), bitangents, bitangentV.size() * sizeof(bitangentV[0]));
	}
	else {
		std::fill(bitangentV.begin(), bitangentV.end(), 0.f);
	}

	return gapi->CreateGeometry(vertexV, indexV, normalV, uvV, tangentV, bitangentV);
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
