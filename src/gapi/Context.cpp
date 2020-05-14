#include "Context.h"
#include "RenderPass.h"
#include "Scene.h"

#include <algorithm>

namespace gapi {
	Context::Context(wnd::Window& window) : m_window(window) {}

	void Context::AddRenderPass(RenderPass* renderPass, int priority) {
		if (!(renderPass && renderPass->IsValid())) {
			return;
		}
		m_renderPasses.emplace(priority, renderPass);
	}

	void Context::RemoveRenderPass(RenderPass* renderPass) {
		if (!(renderPass && renderPass->IsValid())) {
			return;
		}

		auto finded = std::find_if(m_renderPasses.begin(), m_renderPasses.end(), [renderPass](auto rp) { return *renderPass == *rp.second; });
		if (finded != m_renderPasses.end()) {
			m_renderPasses.erase(finded);
		}
	}
	void Context::Draw(const Scene * scene)
	{
		if (!scene) {
			return;
		}

		m_window.clearRenderers();
		for (auto rp : m_renderPasses) {
			RenderPass* renderPass = rp.second;

			renderPass->SetCamera(scene->GetCamera());

			for (auto geom : scene->GetGeometries()) {
				renderPass->SetGeometry(geom);
			}
			m_window.addRenderer(renderPass);
		}

		m_window.draw();
	}
}