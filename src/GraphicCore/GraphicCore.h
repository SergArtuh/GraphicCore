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

#include "Common/Vector.h"

using I32 = int32_t;
using CI32 = const int32_t;
using UI32 = uint32_t;
using CUI32 = const uint32_t;

using Size = const uint64_t;
using CSize = const uint64_t;

using Str = char* const;
using CStr = const char* const;


extern "C" {
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

	void SceneAddGeometry(gapi::Scene * scene, gapi::Geometry* geometry);

	void SceneRemoveGeometry(gapi::Scene* scene, gapi::Geometry* geometry);

	gapi::ShaderSource * CreateShaderSource(CStr sourcr, I32 type);

	void DeleteShaderSource(gapi::ShaderSource* shaderSource);

	gapi::Shader * CreateShader(gapi::Gapi* gapi, gapi::ShaderSource** sources, UI32 count);

	void DeleteShader(gapi::Gapi* gapi, gapi::Shader * shader);


	gapi::RenderPass* CreateRenderPass(gapi::Gapi* gapi, gapi::Shader * shader);

	void DeleteRenderPass(gapi::Gapi* gapi, gapi::RenderPass * renderPass);


	gapi::Geometry * CreateGeometry(gapi::Gapi* gapi, float * vertices, CSize vertexN, UI32 * indexes, CSize indexN);

	void DeleteGeometry(gapi::Gapi* gapi, gapi::Geometry*);

	void Draw(gapi::Gapi * gapi, gapi::Context * context, gapi::Scene * scene);

}
