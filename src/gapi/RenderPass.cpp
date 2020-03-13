#include "RenderPass.h"
#include "Shader.h"
#include "Geometry.h"

#include "wnd/window.h"

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

	void RenderPass::SetInput(RenderPassInput * input, int location) {
		if (!(input && input->IsValid())) {
			return;
		}

		m_shader->GetShaderLLr().SetConstantBuffer(input->GetConstantBuffer(), location);
	}

	void RenderPass::SetGeometry(Geometry * geometry) {
		if (!(geometry && geometry->IsValid())) {
			return;
		}
		m_shader->SetGeometry(*geometry);
	}

	void RenderPass::OnRender(wnd::Window& window)
	{
		window.makeContextCurrent();
		m_shader->Draw();
	}
	bool RenderPass::IsValid() const
	{
		return m_id != UNUSED && m_shader->IsValid();
	}
}