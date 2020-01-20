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

	void RenderPass::SetGeometry(const Geometry * geometry) {
		if (!(geometry && geometry->IsValid())) {
			return;
		}

		m_vertexBuffers.emplace(0, geometry->GetVertexBuffer());
		m_indexBuffer = geometry->GetIndexBuffer();
	}

	void RenderPass::OnRender(wnd::Window& window)
	{
		window.makeContextCurrent();

		for (auto vb : m_vertexBuffers) {
			llr::VertexBuffer vertexBuffer = vb.second;
			
			if (vertexBuffer.IsValid()) {
				int location = vb.first;
				m_shader->GetShaderLLr().SetVertexBuffer(vertexBuffer, location);
			}
		}

		if (m_indexBuffer.IsValid()) {
			m_shader->GetShaderLLr().SetIndexBuffer(m_indexBuffer);
		}

		m_shader->GetShaderLLr().Draw();
	}
	bool RenderPass::IsValid() const
	{
		return m_id != UNUSED && m_shader->IsValid();
	}
}