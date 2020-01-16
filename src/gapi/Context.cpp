#include "Context.h"
#include "RenderPass.h"
#include "Scene.h"

namespace gapi {
	Context::Context(wnd::Window& window) : m_window(window) {}

	void Context::AddRenderPass(RenderPass* renderPass, int priority) {
		m_renderPasses.emplace(priority, renderPass);
	}

	void Context::RemoveRenderPass(RenderPass* renderPass) {
		auto finded = std::find(m_renderPasses.begin(), m_renderPasses.end(), renderPass);
		if (finded != m_renderPasses.end()) {
			m_renderPasses.erase(finded);
		}
	}
	void Context::Draw(const Scene * scene)
	{
		for (auto rp : m_renderPasses) {
			for (auto geom : scene->GetGeometries()) {
				rp.second->SetGeometry(geom);
			}
		}
		m_window.draw();
	}
}