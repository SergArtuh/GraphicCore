#include "RenderPass.h"

#include "wnd/window.h"

#include "RenderPassStage.h"
#include "Shader.h"
#include "Geometry.h"
#include "Camera.h"

constexpr const int IB = 0;
constexpr const int VB = 1;

inline I32 genId() {
	static I32 id = 0;
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

	void RenderPass::SetCamera(CCamera* camera) {
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

			for (const auto input : stage->GetTextures2D()) {
				const auto location = input.first;
				const auto texture2d = input.second->GetTexture2D();

				m_shader->GetShaderLLr().SetTexture2D(texture2d, location);
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
		return m_id != UNUSED && m_shader && m_shader->IsValid();
	}
}