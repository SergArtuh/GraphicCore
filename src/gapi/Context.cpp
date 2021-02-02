#include "Context.h"
#include "RenderPass.h"
#include "RenderPassStage.h"
#include "Scene.h"

#include <algorithm>

namespace gapi {
	Context::Context(wnd::Window& window) : m_window(window) {}

	void Context::AddRenderPass(RenderPass* renderPass, I32 priority) {
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


	void Context::SetupRenderPass(const Scene* scene, RenderPass * renderPass) {
		for (auto stage : renderPass->GetRenderPassStage()) {

			auto geometryTarget = stage->GetGeometryTarget();

			if (ERenderPassInputGeometryTarget::ALL_SCENE == geometryTarget) {
				stage->CleanGeomerties();
				for (auto geom : scene->GetGeometries()) {
					stage->AddGeomerty(geom);
				}
			}
			else if (ERenderPassInputGeometryTarget::NDC_RECT == geometryTarget){
				//TODO:
			}
			else if (ERenderPassInputGeometryTarget::NONE == geometryTarget) {
				stage->CleanGeomerties();
			}
			else if (ERenderPassInputGeometryTarget::CUSTOM == geometryTarget) {
				//no-op
			}
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
			SetupRenderPass(scene, renderPass);

			m_window.addRenderer(renderPass);
		}

		m_window.draw();
	}
}