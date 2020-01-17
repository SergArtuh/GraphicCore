#include "gapi.h"
#include "wnd/window.h"
#include "llr/Shader.h"

#include "Context.h"
#include "Scene.h"
#include "Shader.h"
#include "RenderPass.h"
#include "Geometry.h"

namespace gapi {
	Gapi::Gapi(wnd::Window& window) : m_llr(window), m_context(new Context(window)) {
		
	}

	Gapi::Gapi(const Gapi& r) : m_llr(r.m_llr), m_context(r.m_context) {
		
	}

	Gapi::~Gapi() {
		if (m_context) {
			delete m_context;
			m_context = nullptr;
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
		return new RenderPass(m_context, shader);
	}

	void Gapi::DeleteRenderPass(RenderPass* renderPass) {
		if (renderPass) {
			delete renderPass;
		}
	}

	void Gapi::AddRenderPass(RenderPass* renderPass)
	{
		m_context->AddRenderPass(renderPass);
	}

	void Gapi::RemoveRenderPass(RenderPass* renderPass)
	{
		m_context->RemoveRenderPass(renderPass);
	}

	Geometry* Gapi::CreateGeometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes) {
		return new Geometry(vertices3f, indexes);
	}

	void Gapi::DeleteGeometry(Geometry* geometry) {
		if (geometry) {
			delete geometry;
		}
	}
	void Gapi::Draw(Scene* scene)
	{
		m_context->Draw(scene);
	}
}