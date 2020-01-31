#pragma once

#include "api.h"
#include "wnd/window.h"
#include "gapi/gapi.h"
#include "gapi/Context.h"
#include "gapi/Scene.h"
#include "gapi/Shader.h"
#include "gapi/RenderPass.h"
#include "gapi/Geometry.h"

#include "llr/Shader.h"



extern "C" {
	using CStr = const char* const;
	using CSize = const uint64_t;

	wnd::Window * CreateWindow(const size_t w, const size_t h, CStr title);
	void DeleteWindow(wnd::Window * window);


	gapi::Gapi* CreateGapi(wnd::Window* window);
	void DeleteGapi(gapi::Gapi*);


	gapi::Context* CreateContext(gapi::Gapi * gapi);

	void DeleteContext(gapi::Gapi * gapi, gapi::Context * context);

	void ContextAddRenderPass(gapi::Gapi* gapi, gapi::Context* context, gapi::RenderPass* renderPass);

	void ContextRemoveRenderPass(gapi::Gapi* gapi, gapi::Context* context, gapi::RenderPass* renderPass);


	gapi::Scene* CreateScene(gapi::Gapi * gapi);

	void DeleteScene(gapi::Gapi* gapi, gapi::Scene* scene);

	void SceneAddGeometry(gapi::Scene * scene, gapi::Geometry* geometry);

	void SceneRemoveGeometry(gapi::Scene* scene, gapi::Geometry* geometry);

	gapi::ShaderSource * CreateShaderSource(CStr sourcr, int32_t type);

	void DeleteShaderSource(gapi::ShaderSource* shaderSource);

	gapi::Shader * CreateShader(gapi::Gapi* gapi, gapi::ShaderSource** sources, uint32_t count);

	void DeleteShader(gapi::Gapi* gapi, gapi::Shader * shader);


	gapi::RenderPass* CreateRenderPass(gapi::Gapi* gapi, gapi::Shader * shader);

	void DeleteRenderPass(gapi::Gapi* gapi, gapi::RenderPass * renderPass);


	gapi::Geometry * CreateGeometry(gapi::Gapi* gapi, float * vertices, CSize vertexN, uint32_t * indexes, CSize indexN);

	void DeleteGeometry(gapi::Gapi* gapi, gapi::Geometry*);

	void Draw(gapi::Gapi * gapi, gapi::Context * context, gapi::Scene * scene);

}
