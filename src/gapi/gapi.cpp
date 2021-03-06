#include "gapi.h"
#include "wnd/window.h"
#include "llr/Shader.h"

#include "Context.h"
#include "Scene.h"
#include "Shader.h"
#include "RenderPass.h"
#include "Geometry.h"

namespace gapi {
	Gapi::Gapi(wnd::Window& window) : m_llr(window) {
		
	}

	Gapi::Gapi(const Gapi& r) : m_llr(r.m_llr) {
		
	}

	Gapi::~Gapi() {}

	Context* Gapi::CreateContext()
	{
		return new Context(m_llr.GetWindow());
	}

	void Gapi::DeleteContext(Context* context)
	{
		if (context) {
			delete context;
		}
	}

	Scene* Gapi::CreateScene() {
		return new Scene;
	}

	void Gapi::DeleteScene(Scene * scene) {
		if (scene) {
			delete scene;
		}
	}

	Shader* Gapi::CreateShader(const std::list<ShaderSource> & sources) {
		return new Shader(sources);
	}

	void Gapi::DeleteShader(Shader* shader) {
		if (shader) {
			delete shader;
		}
	}

	RenderPass* Gapi::CreateRenderPass(Shader * shader) {
		return new RenderPass(shader);
	}

	void Gapi::DeleteRenderPass(RenderPass* renderPass) {
		if (renderPass) {
			delete renderPass;
		}
	}

	void Gapi::ContextAddRenderPass(Context* context, RenderPass* renderPass)
	{
		context->AddRenderPass(renderPass);
	}

	void Gapi::ContextRemoveRenderPass(Context* context, RenderPass* renderPass)
	{
		context->RemoveRenderPass(renderPass);
	}

	Geometry* Gapi::CreateGeometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes) {
		return new Geometry(vertices3f, indexes);
	}

	void Gapi::DeleteGeometry(Geometry* geometry) {
		if (geometry) {
			delete geometry;
		}
	}
	void Gapi::Draw(Context* context, Scene* scene)
	{
		context->Draw(scene);
	}
}