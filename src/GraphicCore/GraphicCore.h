#pragma once

#include "api.h"
#include "wnd/window.h"
#include "gapi/gapi.h"
#include "gapi/Context.h"
#include "gapi/Scene.h"
#include "gapi/Shader.h"
#include "gapi/RenderPass.h"
#include "gapi/RenderPassStage.h"
#include "gapi/RenderPassConstantInput.h"
#include "gapi/RenderPassInstanceArrayInput.h"
#include "gapi/RenderPassOutput.h"
#include "gapi/Texture2D.h"
#include "gapi/Geometry.h"
#include "gapi/Camera.h"

#include "llr/Shader.h"

#include "common/types.h"



extern "C" {

	typedef char* (__stdcall* LogMsgCallback)(const char* const msg);

	wnd::Window * CreateWindow(CSize w, CSize h, CStr title);
	void DeleteWindow(wnd::Window * window);


	gapi::PGapi CreateGapi(wnd::Window* window);
	void DeleteGapi(gapi::PGapi);


	gapi::Context* CreateContext(gapi::Gapi * gapi);

	void DeleteContext(gapi::Gapi * gapi, gapi::Context * context);

	void ContextAddRenderPass(gapi::PGapi gapi, gapi::Context* context, gapi::RenderPass* renderPass);

	void ContextRemoveRenderPass(gapi::PGapi gapi, gapi::Context* context, gapi::RenderPass* renderPass);


	gapi::Scene* CreateScene(gapi::Gapi * gapi);

	void DeleteScene(gapi::PGapi gapi, gapi::Scene* scene);

	[[deprecated]]
	void SceneSetCamera(gapi::Scene* scene, gapi::Camera* camera);

	void SceneAddGeometry(gapi::Scene * scene, gapi::Geometry* geometry);

	void SceneRemoveGeometry(gapi::Scene* scene, gapi::Geometry* geometry);

	gapi::ShaderSource * CreateShaderSource(CStr sourcr, I32 type);

	void DeleteShaderSource(gapi::ShaderSource* shaderSource);

	gapi::PShader CreateShader(gapi::PGapi gapi, gapi::ShaderSource** sources, UI32 count);

	void DeleteShader(gapi::PGapi gapi, gapi::PShader shader);


	gapi::PTexture2D CreateTexture2D(gapi::Gapi * gapi, CSize width, CSize height, I32 format);

	void DeleteTexture2D(gapi::PGapi gapi, gapi::PTexture2D texture2d);

	void WriteTexture2D(gapi::PTexture2D texture2d, CSize xMin, const CSize xMax, CSize yMin, CSize yMax, CData data);

	void SaveTexture2D(gapi::PGapi gapi, gapi::PTexture2D texture2d, CStr path);

	void LoadTexture2D(gapi::PGapi gapi, gapi::PTexture2D texture2d, CStr path);


	gapi::PRenderPassConstantInput CreateRenderPassConstantInput(gapi::PGapi gapi, CSize size);

	void DeleteRenderPassConstantInput(gapi::PGapi gapi, gapi::PRenderPassConstantInput renderPassInput);

	void * GetRenderPassConstantInputDataNativePtr(gapi::PRenderPassConstantInput renderPassInput);

	void MarkDirtyRenderPassConstantInput(gapi::PRenderPassConstantInput renderPassInput);


	gapi::PRenderPassInstanceArrayInput CreateRenderPassInstanceArrayInput(gapi::PGapi gapi, CSize size, I32 type, CSize count);

	void DeleteRenderPassInstanceArrayInput(gapi::PGapi gapi, gapi::PRenderPassInstanceArrayInput instanceArrayInput);

	void WriteRenderPassInstanceArrayInput(gapi::PGapi gapi, gapi::PRenderPassInstanceArrayInput instanceArrayInput, void * arrayData, CSize arrayDataN, CSize offset);


	gapi::PRenderPassOutput CreateRenderPassOutput(gapi::PGapi gapi);

	void DeleteRenderPassOutput(gapi::PGapi gapi, gapi::PRenderPassOutput renderPassOutput);

	void SetRenderPassOutputTexture2d(gapi::PGapi gapi, gapi::PRenderPassOutput renderPassOutput, gapi::PTexture2D texture, UI32 location);


	gapi::PRenderPassStage CreateRenderPassStage(gapi::PGapi gapi);

	void DeleteRenderPassStage(gapi::PGapi gapi, gapi::PRenderPassStage renderPassStage);

	void SetRenderPassStageConstantInput(gapi::PGapi gapi, gapi::PRenderPassStage renderPassStage, gapi::PRenderPassConstantInput renderPassInput, UI32 location);

	void SetRenderPassStageOutput(gapi::PGapi gapi, gapi::PRenderPassStage renderPassStage, gapi::PRenderPassOutput output);

	void SetRenderPassStageTexture2d(gapi::PGapi gapi, gapi::PRenderPassStage renderPassStage, gapi::PTexture2D texture2d, UI32 location);

	void SetRenderPassStageGeometryTarget(gapi::PRenderPassStage renderPassStage, int target);

	void AddRenderPassStageGeometry(gapi::PRenderPassStage renderPassStage, gapi::Geometry* geometry);

	void RemoveRenderPassStageGeometry(gapi::PRenderPassStage renderPassStage, gapi::Geometry* geometry);

	void SetRenderPassInstanceArray(gapi::PRenderPassStage renderPassStage, gapi::PRenderPassInstanceArrayInput, CI32 location = 0);

	void SetRenderPassInstanceCount(gapi::PRenderPassStage renderPassStage, CSize count);


	gapi::RenderPass* CreateRenderPass(gapi::PGapi gapi, gapi::Shader * shader);

	void DeleteRenderPass(gapi::PGapi gapi, gapi::RenderPass * renderPass);

	void AddRenderPassStage(gapi::RenderPass* renderPass, gapi::RenderPassStage* stage);

	[[deprecated]]
	gapi::Camera * CreateCamera(gapi::PGapi gapi, float fov, float aspect, float near, float far);

	[[deprecated]]
	void DeleteCamera(gapi::PGapi gapi, gapi::Camera*);


	gapi::Geometry * CreateGeometry(gapi::PGapi gapi,
		float * vertices, CSize vertexCount,
		UI32 * indexes, CSize indexN,
		float* normals,
		float* uvs, 
		float* tangents,
		float* bitangents
	);



	void DeleteGeometry(gapi::PGapi gapi, gapi::Geometry*);

	void Draw(gapi::Gapi * gapi, gapi::Context * context, gapi::Scene * scene);


	void SetLogCallback(LogMsgCallback callback);
}
