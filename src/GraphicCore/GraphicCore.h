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
	wnd::Window * CreateWindow(const size_t w, const size_t h, const char* title);
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


	gapi::Shader * CreateShader(gapi::Gapi* gapi, int count, int type, const char* const source, ...);

	void DeleteShader(gapi::Gapi* gapi, gapi::Shader * shader);


	gapi::RenderPass* CreateRenderPass(gapi::Gapi* gapi, gapi::Shader * shader);

	void DeleteRenderPass(gapi::Gapi* gapi, gapi::RenderPass * renderPass);


	gapi::Geometry * CreateGeometry(gapi::Gapi* gapi, float * vertices, size_t vertexN, unsigned int * indexes, size_t indexN);

	void DeleteGeometry(gapi::Gapi* gapi, gapi::Geometry*);

	void Draw(gapi::Gapi * gapi, gapi::Context * context, gapi::Scene * scene);

}
