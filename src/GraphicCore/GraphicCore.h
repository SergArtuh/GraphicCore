#pragma once

#include "api.h"
#include "wnd/window.h"
#include "gapi/gapi.h"
#include "gapi/Context.h"
#include "gapi/Scene.h"
#include "gapi/Shader.h"
#include "gapi/RenderPass.h"
#include "gapi/RenderPassStage.h"
#include "gapi/RenderPassInput.h"
#include "gapi/Geometry.h"
#include "gapi/Camera.h"

#include "llr/Shader.h"

#include "common/types.h"



extern "C" {

	typedef char* (__stdcall* LogMsgCallback)(const char* const msg);

	wnd::Window * CreateWindow(CSize w, CSize h, CStr title);
	void DeleteWindow(wnd::Window * window);


	gapi::Gapi* CreateGapi(wnd::Window* window);
	void DeleteGapi(gapi::Gapi*);


	gapi::Context* CreateContext(gapi::Gapi * gapi);

	void DeleteContext(gapi::Gapi * gapi, gapi::Context * context);

	void ContextAddRenderPass(gapi::Gapi* gapi, gapi::Context* context, gapi::RenderPass* renderPass);

	void ContextRemoveRenderPass(gapi::Gapi* gapi, gapi::Context* context, gapi::RenderPass* renderPass);


	gapi::Scene* CreateScene(gapi::Gapi * gapi);

	void DeleteScene(gapi::Gapi* gapi, gapi::Scene* scene);

	[[deprecated]]
	void SceneSetCamera(gapi::Scene* scene, gapi::Camera* camera);

	void SceneAddGeometry(gapi::Scene * scene, gapi::Geometry* geometry);

	void SceneRemoveGeometry(gapi::Scene* scene, gapi::Geometry* geometry);

	gapi::ShaderSource * CreateShaderSource(CStr sourcr, I32 type);

	void DeleteShaderSource(gapi::ShaderSource* shaderSource);

	gapi::Shader * CreateShader(gapi::Gapi* gapi, gapi::ShaderSource** sources, UI32 count);

	void DeleteShader(gapi::Gapi* gapi, gapi::Shader * shader);


	gapi::RenderPassInput * CreateRenderPassInput(gapi::Gapi* gapi, CSize size);

	void DeleteRenderPassInput(gapi::Gapi* gapi, gapi::RenderPassInput* renderPassInput);

	void * GetRenderPassInputDataNativePtr(gapi::RenderPassInput* renderPassInput);

	void MarkDirtyRenderPassInput(gapi::RenderPassInput* renderPassInput);


	gapi::RenderPassStage * CreateRenderPassStage(gapi::Gapi* gapi);

	void DeleteRenderPassStage(gapi::Gapi* gapi, gapi::RenderPassStage* renderPassStage);

	void SetRenderPassStageInput(gapi::Gapi* gapi, gapi::RenderPassStage * renderPass, gapi::RenderPassInput* renderPassInput, UI32 location);

	void SetRenderPassStageGeometryTarget(gapi::RenderPassStage * renderPassStage, int target);

	void AddRenderPassStageGeometry(gapi::RenderPassStage * renderPassStage, gapi::Geometry* geometry);

	void RemoveRenderPassStageGeometry(gapi::RenderPassStage * renderPassStage, gapi::Geometry* geometry);


	gapi::RenderPass* CreateRenderPass(gapi::Gapi* gapi, gapi::Shader * shader);

	void DeleteRenderPass(gapi::Gapi* gapi, gapi::RenderPass * renderPass);

	void AddRenderPassStage(gapi::RenderPass* renderPass, gapi::RenderPassStage* stage);

	[[deprecated]]
	gapi::Camera * CreateCamera(gapi::Gapi* gapi, float fov, float aspect, float near, float far);

	[[deprecated]]
	void DeleteCamera(gapi::Gapi* gapi, gapi::Camera*);

	gapi::Geometry * CreateGeometry(gapi::Gapi* gapi, float * vertices, CSize vertexN, UI32 * indexes, CSize indexN);

	void DeleteGeometry(gapi::Gapi* gapi, gapi::Geometry*);

	void Draw(gapi::Gapi * gapi, gapi::Context * context, gapi::Scene * scene);


	void SetLogCallback(LogMsgCallback callback);
}
