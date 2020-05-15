#include "RenderPass.h"

#include "wnd/window.h"

#include "RenderPassStage.h"
#include "Shader.h"
#include "Geometry.h"
#include "Camera.h"

constexpr const int IB = 0;
constexpr const int VB = 1;

inline int genId() {
	static int id = 0;
	return ++id;
}


namespace gapi {
	RenderPass::RenderPass(Shader * shader) : m_shader(shader), m_id(genId())
	{
	}

	bool RenderPass::operator==(const RenderPass& r)
	{
		return m_id == r.m_id;
	}

	void RenderPass::AddRenderPassStage(RenderPassStage* stage) {
		m_stages.push_back(stage);
	}

	CRenderPassStages & RenderPass::GetRenderPassStage() const {
		return m_stages;
	}

	RenderPassStages & RenderPass::GetRenderPassStage() {
		return m_stages;
	}


	void RenderPass::SetGeometry(Geometry * geometry) {
		if (!(geometry && geometry->IsValid())) {
			return;
		}
		m_shader->SetGeometry(*geometry);
	}

	void RenderPass::SetCamera(const Camera* camera) {
		if (!(camera && camera->IsValid())) {
			return;
		}
		m_shader->SetCamera(*camera);
	}

	void RenderPass::OnRender(wnd::Window& window)
	{
		window.makeContextCurrent();
		
		for (const auto stage : GetRenderPassStage()) {
			for (const auto input : stage->GetRenderPassInputs()) {
				const auto location = input.first;
				const auto buffer = input.second->GetConstantBuffer();

				m_shader->GetShaderLLr().SetConstantBuffer(buffer, location);
			}

			for (const auto geom : stage->GetGeometries()) {
				if (!geom->IsAddedToScene()) {
					continue;
				}

				m_shader->SetGeometry(*geom);
				m_shader->Draw();
			}
		}

		
	}
	bool RenderPass::IsValid() const
	{
		return m_id != UNUSED && m_shader->IsValid();
	}
}